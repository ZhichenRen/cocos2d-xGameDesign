#include "Entity\Weapons\Bullets\Bullet.h"
#include "Entity\Weapons\LongRange.h"
#define PI 3.1415926

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
	if (status == true)
	{
		getSprite()->setVisible(false);
		stopAllActions();
	}
}

void Bullet::setOriginPos(const Point& pos)
{
	m_origin_pos = pos;
}

float Bullet::getDistance()const
{
	Point pos = getPosition();
	float distance = sqrtf((pos.x - m_origin_pos.x) * (pos.x - m_origin_pos.x) + (pos.y - m_origin_pos.y) * (pos.y - m_origin_pos.y));
	return distance;
}

void Bullet::setBulletAction(float degree, int speed)
{
	auto move_action = MoveBy::create(1.0f, Vec2(speed * cos(degree / 180 * PI), speed * sin(degree / 180 * PI)));
	auto attack_action = RepeatForever::create(move_action);
	this->runAction(attack_action);
	setDegree(degree);
}

void Bullet::setDegree(float degree)
{
	m_degree = degree;
}

float Bullet::getDegree() const
{
	return m_degree;
}

void Bullet::setCritRate(float rate)
{
	m_crit_rate = rate;
}

float Bullet::getCritRate()const
{
	return m_crit_rate;
}

Bullet::~Bullet()
{

}