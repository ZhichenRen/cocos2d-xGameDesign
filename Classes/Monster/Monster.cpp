#include "Monster\Monster.h"
#include "Monster/MonsterManager.h"
Monster::Monster() 
{
	m_isAlive = false;
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
		setVisible(true);
	m_isAlive = true;
}

void Monster::hide()
{
	if (getSprite() != NULL)
	{
		setVisible(false);
		m_isAlive = false;
	}
}


bool Monster::isAlive()
{
	return m_isAlive;
}

bool Monster::isTaunted()
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
	if (m_map->isBarrier(worldTar))
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

void Monster::resetPropoties()
{
	m_isAlive = true;
}





void Monster::hit(int damage)
{
	this->m_Hp -= damage;
}

void Monster::bindMap(AdventureMapLayer* map)
{
	m_map = map;
}

void Monster::bindMonsMgr(MonsterManager* monsMgr)
{
	m_monsMgr = monsMgr; 
}

void Monster::hit(int damage, float flyingDegree)
{
	this->m_Hp -= damage;
	this->m_fIsTaunted = 1;
	this->stopAllActions();
	auto curPos = getPosition();
	auto vecToMove = Vec2( 3* cos(flyingDegree / 180 * 3.14), 3* sin(flyingDegree / 180 * 3.14));
	auto targetPos = curPos + vecToMove;
	this->mySetPosition(targetPos);
	/*if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(targetPos))))
	{
		auto move_action = MoveBy::create(0.1f, vecToMove);
		
		this->runAction(move_action);
	}*/
	
}


void Monster::die()
{
	hide();
	auto coin = Coin::create();
	//this->getSprite()->setVisible(false);//怪物消失
	auto ranF = CCRANDOM_0_1();
	if (ranF < BLUERATE)
	{
		auto blue = Blue::create();
		blue->setPosition(this->getPosition() + m_monsMgr->getPosition());
		m_map->addChild(blue,2);
		blue->setRandomPosition();

	}
	coin->setPosition(this->getPosition() + m_monsMgr->getPosition());
	m_map->addChild(coin,1);
}

void Monster::wander()
{
	auto curPos = getPosition();
	auto tarPos = m_fIsFacingRight ? ccp(this->getMonsterSpeed(), 0) + curPos : -ccp(this->getMonsterSpeed(), 0) + curPos;
	
	mySetPosition(tarPos);
}



