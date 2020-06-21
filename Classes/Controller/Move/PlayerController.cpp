#include "Controller/Move/PlayerController.h"
#include "Entity/Weapons/CloseWeapon.h"

bool PlayerController::init()
{
	m_iXSpeed = 0;
	m_iYSpeed = 0;
	this->scheduleUpdate();
	return true;
}

void PlayerController::onEnter()
{
	Node::onEnter();
	registeControllerEvent();
}

void PlayerController::onExit()
{
	Node::onExit();
	_eventDispatcher->removeEventListener(m_listener);
}

void PlayerController::update(float dt)
{
	if (m_controllerListener == NULL)
		return;
	Point curPos = m_controllerListener->getTagPosition();

	curPos.x += m_iXSpeed;
	curPos.y += m_iYSpeed;

	isEncounterBarriers(curPos.x, curPos.y);
	m_controllerListener->setTagPosition(curPos.x, curPos.y);

	playerOperate();
}


void PlayerController::setPlayer(Player* player)
{
	m_player = player;
}

void PlayerController::registeControllerEvent()
{
	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	//键盘被按下时响应
	keyListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);
	//键盘按键被弹回时响应
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	m_listener = keyListener;
}

void PlayerController::animateOperate()
{
	if (getiXSpeed() != 0 || getiYSpeed() != 0)
	{
		if (m_standAnimate != NULL)
		{
			stopAction(m_standAnimate);
			m_standAnimate = NULL;
		}
		if (m_walkAnimate == NULL)
		{
			auto animate = m_player->walk();
			m_walkAnimate = animate;
		}
	}
	else
	{
		if (m_walkAnimate != NULL)
		{
			stopAction(m_walkAnimate);
			m_walkAnimate = NULL;
		}
		if (m_standAnimate == NULL)
		{
			auto animate = m_player->stand();
			m_standAnimate = animate;
		}
	}
}

void PlayerController::isEncounterBarriers(const int x, const int y)
{
	Size spriteSize = m_player->getSprite()->getContentSize();
	Point dstPos = Point(x + m_player->isPositiveOrNegative(m_player->getController()->getiXSpeed()) * 20 +
		m_player->getSkillDirectionX() * 5, y + m_player->isPositiveOrNegative(m_player->
			getController()->getiYSpeed()) * 20 + m_player->getSkillDirectionY() * 5);

	/* 获得当前主角前方坐标在地图中的格子位置 */
	Point tiledPos = m_player->tileCoordForPosition(Point(dstPos.x, dstPos.y));

	// 获取地图格子的唯一标识 
	int tiledGid = (m_player->getMap()->getCollidable())->getTileGIDAt(tiledPos);

	// 不为0，代表存在这个格子 
	if (tiledGid != 0)
	{
		/*
		获取该地图格子的所有属性，目前我们只有一个Collidable属性
		格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性
		时，通过格子唯一标识在地图中取得
		*/
		Value properties = (m_player->getMap()->getMap())->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();

		if (propertiesMap.find("Collidable") != propertiesMap.end())
		{
			/* 取得格子的Collidable属性值 */
			Value prop = propertiesMap.at("Collidable");
			/* 判断Collidable属性是否为true，如果是，则不让玩家移动 */
			if (prop.asString().compare("true") == 0)
			{
				auto moveBy = MoveBy::create(0.01f, Point(-(m_player->isPositiveOrNegative
				(m_player->getController()->getiXSpeed()) + m_player->getSkillDirectionX()) * 5,
					-(m_player->isPositiveOrNegative(m_player->getController()->
						getiYSpeed()) + m_player->getSkillDirectionY()) * 5));

				/* 执行动作，碰撞到障碍物时的反弹效果 */
				if (m_rangerSkill != NULL)
				{
					m_player->stopAction(m_rangerSkill);
					m_rangerSkill = NULL;
				}
				m_player->runAction(moveBy);
			}
		}
	}
}

void PlayerController::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_W)
	{
		//CCLOG("按W：上方向键");
		this->setiYSpeed(4);
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_A)
	{
		//CCLOG("按A：左方向键");
		this->setiXSpeed(-4);
		m_player->setRightToward();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_D)
	{
		//CCLOG("按D：右方向键");
		this->setiXSpeed(4);
		m_player->setLeftToward();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_S)
	{
		//CCLOG("按S：下方向键");
		this->setiYSpeed(-4);
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		//CCLOG("按空格：放技能");
		m_player->skill();
		if (m_isRanger && (m_player->getiNowCD() == 0))
		{
			rangerOpearte();
		}
		
		return;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_player->changeWeapon();
		if (m_isKnight)
		{
			m_player->skillEnd();
		}
	}

	animateOperate();
}


void PlayerController::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_D)
	{
		this->setiXSpeed(0);
	}
	else if(keycode == EventKeyboard::KeyCode::KEY_W || keycode == EventKeyboard::KeyCode::KEY_S)
	{
		this->setiYSpeed(0);
	}
	if (m_walkAnimate != NULL && m_iXSpeed == 0 && m_iYSpeed == 0)
	{
		stopAction(m_walkAnimate);
		m_walkAnimate = NULL;
	}
	if (m_standAnimate == NULL)
	{
		auto animate = m_player->stand();
		m_standAnimate = animate;
	}
	m_isChangWeapon = false;
}

void PlayerController::playerOperate()const
{
	m_player->setiNowCD((m_player->getiNowCD() + 1));
    m_player->setArmorCd();
	if (m_player->getiNowHp() == 0)
		m_player->die();
	if (m_player->getIsInSkill())
	{
		m_player->setiNowSkillDuration(m_player->getiNowSkillDuration() + 1);
		m_player->skillDuration();
		if (m_player->getiNowSkillDuration() == m_player->getiTotalSkillDuration())
			m_player->skillEnd();
	}
}

void PlayerController::rangerOpearte()
{
	auto moveBy = MoveBy::create(0.1, m_player->getSkillDirection());
	auto callFunc = CallFunc::create([&]()
	{
		m_rangerSkill = NULL;
		m_player->setSkillDirectionX(0);
		m_player->setSkillDirectionY(0);
	});
	auto rangerAction = Sequence::create(moveBy, callFunc, NULL);
	m_rangerSkill = rangerAction;
	m_player->runAction(rangerAction);
}

