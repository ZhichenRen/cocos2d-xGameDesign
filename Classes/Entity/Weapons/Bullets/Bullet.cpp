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

void Bullet::setInfo(int range, int damage)
{
	m_bullet_damage = damage;
	m_bullet_range = range;
}

bool Bullet::isUsed()const
{
	return m_is_used;
}

void Bullet::setIsUsed(bool status)
{
	m_is_used = status;
}

void Bullet::setOriginPos(const Point& pos)
{
	m_origin_pos = pos;
}

float Bullet::getDistance()const
{
	Point pos = getPosition();
	float distance = sqrtf((pos.x - m_origin_pos.x)*(pos.x - m_origin_pos.x) + (pos.y - m_origin_pos.y)*(pos.y - m_origin_pos.y));
	return distance;
}

Bullet::~Bullet()
{

}