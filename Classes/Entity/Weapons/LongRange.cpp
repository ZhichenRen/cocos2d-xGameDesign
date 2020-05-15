#include "Entity\Weapons\LongRange.h"
#include "Entity\Weapons\Bullets\Bullet.h"
#include <cmath>
#define PI 3.1415926

LongRange::LongRange()
{
	m_bullet_speed = 1;
	m_bullet_per_sec = 1;
	m_bullet_num = 1;
	m_range = 1;
}

bool LongRange::init()
{
	this->scheduleUpdate();
	return true;
}

void LongRange::attack(Point pos)
{
	if (m_bullet_num == 0)
	{
		return;
	}
	m_bullet_num--;
	Point now = convertToWorldSpace(getSprite()->getPosition());
	float degree;
	float dx = pos.x - now.x;
	float dy = pos.y - now.y;
	if (dx == 0)
	{
		if (dy > 0)
		{
			degree = 90.0f;
		}
		else
		{
			degree = -90.0f;
		}
	}
	else
	{
		degree = atan(dy / dx) / PI * 180;
	}
	getSprite()->setRotation(-degree);
	Bullet* new_bullet = Bullet::create();
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.getCString()), 0.7f, 0.7f);
	if ((degree > 0 && dy < 0 && dx < 0) || (degree < 0 && dy>0 && dx < 0))
	{
		degree += 180;
		getSprite()->setFlippedX(true);
	}
	else
	{
		getSprite()->setFlippedX(false);
	}
	new_bullet->setPosition(getSprite()->getPositionX() + getSprite()->getBoundingBox().size.width*cos(degree / 180 * PI) / 2
		, getSprite()->getPositionY() + getSprite()->getBoundingBox().size.width*sin(degree / 180 * PI) / 2);
	new_bullet->setRotation(-degree);
	new_bullet->setVisible(true);
	this->addChild(new_bullet);
	auto move_action = MoveBy::create(1.0f, Vec2(m_bullet_speed*cos(degree/180*PI), m_bullet_speed*sin(degree/180*PI)));
	auto attack_action = RepeatForever::create(move_action);
	new_bullet->runAction(attack_action);
	m_bullet.push_back(new_bullet);
}

void LongRange::rotate(float time, float degree)
{
	auto rotate_action = RotateTo::create(time, degree);
	getSprite()->runAction(rotate_action);
}

std::vector<Bullet*> LongRange::getBullet()const
{
	return m_bullet;
}

int LongRange::getRange()const
{
	return m_range;
}

int LongRange::getDamage()const
{
	return m_bullet_damage;
}

void LongRange::update(float dt)
{
	auto it = m_bullet.begin();
	while (it != m_bullet.end())
	{
		if ((*it)->isUsed() == true)
		{
			it = m_bullet.erase(it);
			log("Delete");
		}
		else
		{
			it++;
		}
	}
}

LongRange::~LongRange()
{

}