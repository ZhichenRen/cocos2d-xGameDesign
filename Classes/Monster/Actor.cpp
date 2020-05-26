#include "Actor.h"




bool Actor::init()
{
	if (!Entity::init())
	{
		return false;
	}
	return true;
}

void Actor::moveTo(const Vec2& targetPosition)
{
}

bool Actor::getAttacked(int value)
{
	m_Hp -= value;
	return true;
}
