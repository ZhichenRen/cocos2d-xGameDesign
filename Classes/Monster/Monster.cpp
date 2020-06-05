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
		getSprite()->setVisible(true);
	m_isAlive = true;
}

void Monster::hide()
{
	if (getSprite() != NULL)
	{
		getSprite()->setVisible(false);
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
	//this->getSprite()->setVisible(false);//¹ÖÎïÏûÊ§
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