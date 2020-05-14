#include "Entity\Weapons\Bullets\Bullet.h"
#include "Entity\Weapons\LongRange.h"

Bullet::Bullet()
{
	
}

bool Bullet::init()
{
	return true;
}

bool Bullet::isCollideWith(Entity* entity)
{
	return getSprite()->getBoundingBox().intersectsRect(entity->getSprite()->getBoundingBox());
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

Bullet::~Bullet()
{

}