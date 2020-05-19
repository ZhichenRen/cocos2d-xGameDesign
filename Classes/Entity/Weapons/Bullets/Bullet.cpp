#include "Entity\Weapons\Bullets\Bullet.h"
#include "Entity\Weapons\LongRange.h"

Bullet::Bullet()
{
	
}

bool Bullet::init()
{
	m_is_used = false;
	return true;
}

bool Bullet::isCollideWith(Entity* entity)
{
	return getBoundingBox().intersectsRect(entity->getBoundingBox());
}

int Bullet::getRange()const
{
	return m_bullet_range;
}

int Bullet::getDamage()const
{
	return m_bullet_damage;
}

void Bullet::bindWeapon(LongRange* long_range)
{
	m_bullet_damage = long_range->getDamage();
	m_bullet_range = long_range->getRange();
}

bool Bullet::isUsed()const
{
	return m_is_used;
}

void Bullet::setIsUsed(bool status)
{
	m_is_used = status;
}

Bullet::~Bullet()
{

}