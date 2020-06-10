#include "Scene/TollgateScene.h"
#include "Scene/PauseScene.h"
#include "Scene/HomeScene.h"
#include "Entity/Weapons/Bullets/ExplosiveBullet.h"
#include "Entity/Weapons/RPG.h"
#include "Entity/Weapons/Shotgun.h"
#include "GameData.h"

USING_NS_CC;




Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	Director::getInstance()->setProjection(Director::Projection::_2D);
	return scene;
}

void TollgateScene::loadMap()
{
	m_map = AdventureMapLayer::create();
	this->addChild(m_map, 0, 100);//娓告垙鍦板浘 tag涓?00

}

void TollgateScene::addPlayer()
{
	TMXObjectGroup* group = m_map->getMap()->getObjectGroup("objects");//鑾峰彇瀵硅薄灞?
	ValueMap spawnPoint = group->getObject("hero");//鏍规嵁hero瀵硅薄鐨勪綅缃斁缃簿鐏?
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	m_player = Ranger::create();
	m_player->setPosition(Vec2(x, y));

	m_player->setTiledMap(m_map);
	m_player->setCdBar(m_cdBar);
	m_map->addChild(m_player, 2, 200);
}

void TollgateScene::addLongRangeWeapon()
{
	m_player->setLongRange(CandyGun::create());
}

void TollgateScene::loadController()
{
	auto animate = m_player->stand();
	auto* playerController = PlayerController::create();
	playerController->setiXSpeed(0);
	playerController->setiYSpeed(0);
	this->addChild(playerController);
	m_player->setController(playerController);
	playerController->setPlayer(m_player);
	playerController->setIsRanger(typeid(*m_player) == typeid(Ranger));//浠ュ悗涓巑emberSelect缁撳悎
	playerController->setStandAnimate(animate);

}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;

	this->scheduleUpdate();

	loadMap();
	loadUI();
	addPlayer();
	//addLongRangeWeapon();
	loadController();
	loadMonsters();
	loadListeners();

	return true;
}

void TollgateScene::onEnter()
{
	Layer::onEnter();
	loadUI();
	addLongRangeWeapon();
	//loadListeners();
}

void TollgateScene::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("INGAME_1.ExportJson");
	this->addChild(UI, 0, 0);
	m_cdBar = (LoadingBar*)Helper::seekWidgetByName(UI, "ability_loading_bar");

	auto pause_button = (Button*)Helper::seekWidgetByName(UI, "pause_button");
	pause_button->addTouchEventListener(this, toucheventselector(TollgateScene::pauseEvent));
}

void TollgateScene::pauseEvent(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Size visible_size = Director::getInstance()->getVisibleSize();
		CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
		background->begin();
		this->visit();
		background->end();
		Director::getInstance()->pushScene(PauseScene::createScene(background));
		break;
	}
}

void TollgateScene::loadMonstersInNewRoom(int giantNum = -1)
{
	
	auto roomCoord = m_monsterMgr->getCurRoom();
	m_monsterMgr->markRoomVisited(roomCoord);
	auto midPoint = GameData::getCoord()[static_cast<int>(5 * roomCoord.x + roomCoord.y)];
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10,- 10)) * 32;
	m_monsterMgr->setPosition(LUPoint);

	if (giantNum != -1)
		m_monsterMgr->setBulkMonsterNum(giantNum);
	if (!m_monsterMgr->getInited())
	{
		m_monsterMgr->createMonstersWithGiantNum();
		m_monsterMgr->createMonsterPos();
		m_monsterMgr->setInited();
		return;
	}
	m_monsterMgr->reviveAllMonsters();
}


void TollgateScene::loadMonsters()
{
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);
	//绑定房间
	m_monsterMgr = MonsterManager::create();
	//设置位置
	auto midPoint = GameData::getCoord()[static_cast<int>(5 * roomCoord.x + roomCoord.y)];
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10, -10)) * 32;
	m_monsterMgr->setPosition(LUPoint);

	//初始化工作
	m_monsterMgr->bindMap(m_map);
	m_monsterMgr->bindPlayer(static_cast<Entity*>(this->m_player));
	m_map->addChild(m_monsterMgr, 2);
}

void TollgateScene::loadListeners()
{
	auto pause_listener = EventListenerKeyboard::create();
	pause_listener->onKeyPressed = [](EventKeyboard::KeyCode key, Event* event)
	{
		return true;
	};
	pause_listener->onKeyReleased = [=](EventKeyboard::KeyCode key, Event* event)
	{
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_E:
			GameData::setCoinNum(GameData::getCoinNum() + 1);
			if (ccpDistance(m_player->getPosition(), m_map->getChest()->getPosition()) < 20.0f && m_map->getChest()->isVisible())
			{
				m_map->getChest()->setVisible(false);
				m_map->getChest()->setWeapon(rand() % 3 + 1);
				m_player->setLongRange(m_map->getChest()->getWeapon());
			}
			else if (ccpDistance(m_player->getPosition(), m_map->getShop()->getPosition()) < 20.0f)
			{
				if (m_map->getShop()->getInteractionNum() == 1)//第一次互动
				{
					m_map->getShop()->setInteractionNum(2);
					m_map->getShop()->showFlowWordFirstMeet();
				}
				else
				{
					if (GameData::getCoinNum() >= m_map->getShop()->getPrice())
					{
						GameData::setCoinNum(GameData::getCoinNum() - 20);
						m_map->getShop()->setWeapon(rand() % 3 + 1);
						m_player->setLongRange(m_map->getShop()->getWeapon());
						m_map->getShop()->showFlowWordEnoughMoney();
					}
					else
					{
						m_map->getShop()->showFlowWordLackMoney();
					}
					m_map->getShop()->setInteractionNum(1);
				}
			}
			if (ccpDistance(m_player->getPosition(), m_map->getPortal()->getPosition()) < 20.0f)
			{
				this->unscheduleUpdate();
				if (GameData::getLevel() != 2)
				{
					GameData::setLastRoomCoord(Vec2(2, 2));
					GameData::setLevel(GameData::getLevel() + 1);
					auto scene = TollgateScene::createScene();
					Director::getInstance()->replaceScene(scene);
				}
				else
				{
					GameData::setLastRoomCoord(Vec2(2, 2));
					GameData::setLevel(1);
					auto scene = HomeMenuLayer::createScene();
					Director::getInstance()->replaceScene(scene);
				}
			}
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Size visible_size = Director::getInstance()->getVisibleSize();
			CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
			background->begin();
			this->visit();
			background->end();
			Director::getInstance()->pushScene(PauseScene::createScene(background));
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pause_listener, this);
}



void TollgateScene::updateMiniMap(TMXTiledMap* miniMap)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto miniMapLayer = miniMap->getLayer("miniMapLayer");
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);

	miniMap->setPosition(m_map->convertToNodeSpace(this->getPosition()) + Vec2(700, 400));

	if (roomCoord == Vec2(-1, -1))
	{
		return;
	}

	miniMapLayer->setTileGID(2, 2 * GameData::getLastRoomCoord());//浅灰
	miniMapLayer->setTileGID(1, 2 * Vec2(roomCoord.y, roomCoord.x));//深灰

	if (GameData::getLastRoomCoord() != Vec2(roomCoord.y, roomCoord.x))
	{
		if (GameData::getLastRoomCoord().x == roomCoord.y)//上下相连
		{
			miniMapLayer->setTileGID(4, GameData::getLastRoomCoord() + Vec2(roomCoord.y, roomCoord.x));
		}
		else//左右相连
		{
			miniMapLayer->setTileGID(3, GameData::getLastRoomCoord() + Vec2(roomCoord.y, roomCoord.x));
		}
	}
	GameData::setLastRoomCoord(Vec2(roomCoord.y, roomCoord.x));
}

void TollgateScene::updateCoinNum()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto n = this->getChildByTag(101);
	if (n)
	{
		this->removeChildByTag(101);
	}
	auto num = __String::createWithFormat("%d", GameData::getCoinNum());
	auto coinLabel = Label::createWithTTF(num->getCString(), "fonts/arial.ttf", 30);

	coinLabel->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 600));
	this->addChild(coinLabel, 20, 101);
}

void TollgateScene::update(float dt)
{
	auto playerPos = m_player->getPosition();
	auto barrier = m_map->getCollidable();
	auto map = m_map->getMap();
	auto miniMap = m_map->getMiniMap();
	auto wall = m_map->getWall();
	auto roadPairs = m_map->getRoadPairs();
	updateMiniMap(miniMap);

	updateCoinNum();

	auto roomCoord = m_map->roomCoordFromPosition(playerPos);//鎴块棿鍧愭爣
	auto roomNum = roomCoord.x * 5 + roomCoord.y;//鎴块棿搴忓彿

	if (m_map->isMonsterRoom(roomCoord)	//首先它得是个怪物房间
		&&!m_monsterMgr->isRoomVisited(roomCoord))//其次它没有被到访过
	{
		m_monsterMgr->setCurRoom(roomCoord);
		loadMonstersInNewRoom(2);
	}
	Vec2 dir[4] = { {0,1},{0,-1},{1,0},{-1,0} };//鍥涗釜鏂瑰悜

	if (true)//杩涘叆鏈夋�墿鐨勬埧闂达紝寮�濮嬫垬鏂?
	{
		miniMap->setVisible(false);
		std::vector<int>dirVec;
		for (int i = 0; i < 4; i++)
		{
			for (auto elem : roadPairs)
			{
				if (elem.first == roomCoord && elem.second == dir[i] + roomCoord ||
					elem.second == roomCoord && elem.first == dir[i] + roomCoord)
				{
					dirVec.push_back(i);
				}
			}
		}
		for (auto elem : dirVec)
		{
			AdventureMapLayer::switchGate(wall, barrier, roomNum, elem, true);
		}
		//auto t = time(nullptr);
		if (m_monsterMgr->isGameOver())//缁撴潫鎴樻枟
		{
			for (auto elem : dirVec)
			{
				AdventureMapLayer::switchGate(wall, barrier, roomNum, elem, false);
			}
			miniMap->setVisible(true);
		}
	}

	//碰撞检测
	auto player_bullet = m_player->getBullet();
	auto monsters_bullet = m_monsterMgr->getMonsterBullets();
	auto monsters = m_monsterMgr->getMonster();

	//player bullet
	for (auto bullet : player_bullet)
	{
		if (bullet->isUsed())
		{
			continue;
		}
		cocos2d::Point bullet_pos = bullet->getPosition();
		if (m_map->isBarrier(bullet_pos))
		{
			if (typeid(*bullet) == typeid(ExplosiveBullet))
			{
				auto explosive_bullet = dynamic_cast<ExplosiveBullet*>(bullet);
				if (!explosive_bullet->isUsed() && !explosive_bullet->isExplode())
				{
					explosive_bullet->explode();
				}
				for (auto unlucky_monster : monsters)
				{
					if (unlucky_monster->isAlive())
					{
						cocos2d::Point explosive_origin_point = m_map->convertToWorldSpace(explosive_bullet->getPosition());
						if (unlucky_monster->getBoundingBox().intersectsCircle(explosive_origin_point, explosive_bullet->getExplosionRange()))
						{
							unlucky_monster->hit(explosive_bullet->getExplosionDamage());
						}
					}
				}
			}
			else bullet->setIsUsed(true);
		}
		for (auto monster : monsters)
		{
			if (monster->isAlive())
			{
				if (bullet->isCollideWith(monster))
				{

					int damage = bullet->getDamage();
					if (CCRANDOM_0_1() < bullet->getCritRate())
					{
						damage *= 2;
						monster->hit(damage, bullet->getDegree(), 1);
					}
					else
						monster->hit(damage, bullet->getDegree(), 0);

					
					if (typeid(*bullet) == typeid(ExplosiveBullet))
					{
						auto explosive_bullet = dynamic_cast<ExplosiveBullet*>(bullet);
						if (!explosive_bullet->isUsed() && !explosive_bullet->isExplode())
						{
							explosive_bullet->explode();
						}
						for (auto unlucky_monster : monsters)
						{
							if (unlucky_monster->isAlive())
							{
								cocos2d::Point explosive_origin_point = m_map->convertToWorldSpace(explosive_bullet->getPosition());
								if (unlucky_monster->getBoundingBox().intersectsCircle(explosive_origin_point, explosive_bullet->getExplosionRange()))
								{
									unlucky_monster->hit(explosive_bullet->getExplosionDamage(), explosive_bullet->getDegree(), 1);
								}
							}
						}
					}
					else bullet->setIsUsed(true);
				}
			}
		}			
	}

	//monster bullet
	for (auto bullet : monsters_bullet)
	{
		cocos2d::Point bullet_pos = bullet->getPosition();
		if (m_map->isBarrier(bullet_pos))
		{
			bullet->setIsUsed(true);
		}
		if (bullet->isCollideWith(m_player))
		{
			m_player->hit(bullet->getDamage());
			bullet->setIsUsed(true);
		}
	}

	for (auto coin : m_map->getCoinList())
	{
		if (ccpDistance(coin->getPosition(), m_player->getPosition()) < 20.0f && coin->isVisible())
		{
			coin->setVisible(false);
			GameData::setCoinNum(GameData::getCoinNum() + 1);
		}
	}
}