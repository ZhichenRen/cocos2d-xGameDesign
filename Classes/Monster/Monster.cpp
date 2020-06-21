#include "Monster\Monster.h"
#include "Monster/MonsterManager.h"
#include <string>
Monster::Monster()
{
	m_preRec = Sprite::create("PreRect.png");
	this->addChild(m_preRec, 1, "preRect");
	//this->getChildByName("preRect")->setVisible(false);
	m_isAlive = false;
}
bool Monster::isCollideWith(Entity* entity)
{
	return getBoundingBox().intersectsRect(entity->getBoundingBox());
}
Monster::~Monster()
{
	//this->autorelease();
}

bool Monster::init()
{

	return true;
}

void Monster::show()
{
	if (getSprite())
	{
		m_sprite->setVisible(true);
		m_sprite->setOpacity(255);
		//m_weapon->setVisible(false);
	}
	m_isAlive = true;
}

void Monster::hide()
{
	if (getSprite() != NULL)
	{
		//m_sprite->setVisible(false);
		m_weapon->getSprite()->setVisible(false);
		m_isAlive = false;
	}
}


bool Monster::isAlive()const
{
	return m_isAlive;
}

bool Monster::isTaunted()const
{
	return m_fIsTaunted;
}

bool Monster::setTaunted(bool flag)
{
	return m_fIsTaunted = flag;
}

bool Monster::mySetPosition(Vec2 target)
{//重构，所有的方位都要进这个函数
	auto curPos = getPosition();
	auto worldTar = target + m_monsMgr->getPosition();//是一种很好的写法哦
	Vec2 tarBlock = ccp(static_cast<int>(target.x) / 21, static_cast<int>(target.y) / 21);
	auto curBlock = ccp(static_cast<int>(curPos.x) / 21, static_cast<int>(curPos.y) / 21);
	m_monsMgr->setPosMap(curBlock, 0);
	if (m_map->isBarrier(worldTar)
		|| m_monsMgr->isPosOccupied(tarBlock))
	{
		if (!this->isTaunted())
		{
			m_fIsFacingRight = !m_fIsFacingRight;
			m_sprite->setFlipX(m_fIsFacingRight);
		}
		return false;
	}

	if (m_monsMgr->isPosOccupied(tarBlock))
		return false;

	auto dif = target - curPos;
	if (dif.x > 0 && !m_fIsFacingRight)	//面朝左但是跑向右		
	{
		m_fIsFacingRight = true;
		m_sprite->setFlipX(true);
	}
	else if (dif.x < 0 && m_fIsFacingRight)//面朝右但是跑向左
	{
		m_fIsFacingRight = false;
		m_sprite->setFlipX(false);
	}
	setPosition(target);
	m_monsMgr->setPosMap(tarBlock, 1);

	return true;
}

void Monster::bulkUp()
{
	m_fSpeed *= 1.3;
	setContentSize(Size(getContentSize().width * 2, getContentSize().height * 2));
	getSprite()->setContentSize(Size(getSprite()->getContentSize().width * 2, getSprite()->getContentSize().height * 2));
	m_Hp *= 2.0;
	auto weapon = getMonsterWeapon();
	weapon->setAttackSpeed(weapon->getAttackSpeed() * 1.5f);
	weapon->setDamage(weapon->getDamage() * 1.5);
	m_isBulkUp = true;
}

void Monster::resetPropoties()
{
}









void Monster::bindMap(AdventureMapLayer* map)
{
	m_map = map;

}

void Monster::bindMonsMgr(MonsterManager* monsMgr)
{
	m_monsMgr = monsMgr;
}

void Monster::hit(int damage)
{
	if (!m_isAlive)
		return;
	setMonsTaunted();
	this->m_Hp -= damage;
	std::string msg = '-' + std::to_string(damage);
	m_damageMsg->showMonsDmg(msg.c_str(), this->getContentSize().height / 2);
}


void Monster::hit(int damage, float flyingDegree, bool isCriticalStrike)
{
	if (!m_isAlive)
		return;
	this->m_Hp -= damage;
	setMonsTaunted();
	this->stopAllActions();
	auto curPos = getPosition();
	auto vecToMove = Vec2(5 * cos(flyingDegree / 180 * 3.14), 5 * sin(flyingDegree / 180 * 3.14));
	if (m_isBulkUp)
		vecToMove *= 3;
	auto targetPos = curPos + vecToMove;

	this->mySetPosition(targetPos);
	/*if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(targetPos))))
	{
		auto move_action = MoveBy::create(0.1f, vecToMove);
		this->runAction(move_action);
	}*/
	if (isCriticalStrike)
	{
		std::string msg = std::to_string(damage) + '!';
		m_damageMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2);
		return;
	}
	std::string msg = std::to_string(damage);
	m_damageMsg->showMonsDmg(msg.c_str(), this->getContentSize().height / 2);
}



void Monster::die()
{

	m_isAlive = false;
	auto fade = FadeTo::create(1.0f, 0);//消失至某一透明度
	/*auto disappear_delay = DelayTime::create(2.0f);
	auto disappear = FadeTo::create(0.5f, 0);
	auto disappear_action = Sequence::create(fade, disappear_delay, disappear, NULL);*/
	this->getSprite()->runAction(fade);
	if (m_weapon)
	{
		m_weapon->getSprite()->setVisible(false);
	}
	auto coin = Coin::create();
	//this->getSprite()->setVisible(false);//怪物消失
	auto ranF1 = CCRANDOM_0_1();
	if (ranF1 < BLUERATE)
	{
		auto blue = Blue::create();
		blue->setPosition(this->getPosition() + m_monsMgr->getPosition());
		m_map->addChild(blue, 2);
		blue->setRandomPosition();
		m_map->addBlue(blue);
	}
	auto ranF2 = CCRANDOM_0_1();
	if (ranF2 < REDRATE)
	{
		auto red = Red::create();
		red->setPosition(this->getPosition() + m_monsMgr->getPosition());
		m_map->addChild(red, 2);
		red->setRandomPosition();
		m_map->addRed(red);
	}
	coin->setPosition(this->getPosition() + m_monsMgr->getPosition());
	auto ranF3 = CCRANDOM_0_1();
	if (ranF3 < BLUEMEDICINERATE)
	{
		auto blueMedicine = BlueMedicine::create();
		blueMedicine->setPosition(this->getPosition() + m_monsMgr->getPosition());
		m_map->addChild(blueMedicine, 2);
		blueMedicine->setRandomPosition();
		m_map->addBlueMedicine(blueMedicine);
	}
	coin->setPosition(this->getPosition() + m_monsMgr->getPosition());
	m_map->addChild(coin, 1);
	m_map->addCoin(coin);
}

void Monster::wander()
{
	auto curPos = getPosition();

	auto tarPos = m_fIsFacingRight ? ccp(this->getMonsterSpeed(), 0) +
		curPos : -ccp(this->getMonsterSpeed(), 0) + curPos;

	mySetPosition(tarPos);
}



void Monster::setMonsTaunted()
{
	if (isTaunted())
		return;
	m_fIsTaunted = 1;
	m_damageMsg->showMonsTaunted();

}

FlowWord* Monster::getFlowWord() const
{
	return m_damageMsg;
}

