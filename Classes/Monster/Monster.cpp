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

bool Monster::mySetPosition(Vec2 target)
{//重构，所有的方位都要进这个函数
	auto worldTar = target + m_monsMgr->getPosition();//是一种很好的写法哦
	Vec2 tarBlock = ccp(static_cast<int>(target.x) / 21, static_cast<int>(target.y) / 21);

	if (m_map->isBarrier(worldTar))
		return false;
	if (m_monsMgr->isPosOccupied(tarBlock))
		return false;
	auto curPos = this->getPosition();
	auto dif = target - curPos;
	if (dif.x > 1 && !m_fIsFacingRight)	//面朝左但是跑向右		
	{
		m_sprite->setFlipX(true);
		m_fIsFacingRight = 1;
	}
	else if (dif.x < 0 && m_fIsFacingRight)//面朝右但是跑向左
	{
		m_sprite->setFlipX(false);
		m_fIsFacingRight = 0;
	}
	setPosition(target);
	m_monsMgr->setPosMap(tarBlock, 1);
	return true;
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
	auto curPos = getPosition();
	auto vecToMove = Vec2(5 * cos(flyingDegree / 180 * 3.14), 5 * sin(flyingDegree / 180 * 3.14));
	auto targetPos = curPos + vecToMove;
	if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(targetPos))))
	{
		auto move_action = MoveBy::create(0.1f, vecToMove);
		
		this->runAction(move_action);
	}
	
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
		blue->setPosition(this->getPosition());
		this->getParent()->addChild(blue);
		blue->setRandomPosition();

	}
	coin->setPosition(this->getPosition());
	this->getParent()->addChild(coin);
}