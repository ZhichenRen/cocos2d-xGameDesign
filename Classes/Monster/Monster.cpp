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
	if (getSprite() != NULL)
	{
		setVisible(true);
		m_isAlive = true;
	}
}

void Monster::hide()
{
	if (getSprite() != NULL)
	{
		removeAllChildren();
		m_isAlive = false;
	}
}


bool Monster::isAlive()
{
	return m_isAlive;
}


void Monster::moveTo(const Vec2& targetPosition)
{
	auto move = MoveTo::create(1.0f,
		Vec2(targetPosition.x, targetPosition.y));
	this->runAction(move);
}

void Monster::moveBy(const Vec2& distance)
{
	auto move = MoveTo::create(1.0f,
		Vec2(distance.x, distance.y));
	this->runAction(move);
}

void Monster::hit(int damage)
{
	this->m_Hp -= damage;
}


void Monster::die()
{
	hide();
	auto coin = Coin::create();
	this->getSprite()->setVisible(false);//¹ÖÎïÏûÊ§
	this->addChild(coin);
}