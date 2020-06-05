#include "Monster\Monster.h"
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

void Monster::mySetPosition(Vec2 target)
{
	auto curPos = this->getPosition();
	auto dif = target - curPos;
	if (dif.x > 1 && !m_fIsFacingRight)	//面朝左但是跑向右		
	{
		m_sprite->setFlipX(true);
		m_fIsFacingRight = 1;
	}
	else if (dif.x < 0 && m_fIsFacingRight)//面朝右但是跑向右
	{
		m_sprite->setFlipX(false);
		m_fIsFacingRight = 0;
	}
	setPosition(target);
}





void Monster::hit(int damage)
{
	this->m_Hp -= damage;
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