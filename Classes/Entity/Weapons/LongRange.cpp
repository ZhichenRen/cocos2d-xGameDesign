#include "Entity\Weapons\LongRange.h"
#include "Entity\Weapons\Bullets\Bullet.h"
#include <cmath>
#define PI 3.1415926

LongRange::LongRange()
{
}

bool LongRange::init()
{
	m_bullet_speed = 1;
	m_attack_speed = 1.0f;
	m_bullet_num = 1;
	m_range = 1;
	m_is_attack = false;
	this->scheduleUpdate();
	return true;
}

void LongRange::attack(Point pos)
{
	if (m_is_attack == true)
	{
		return;
	}
	if (m_bullet_num == 0)
	{
		return;
	}
	m_is_attack = true;
	m_bullet_num--;
	Point weapon_pos = m_sprite->getPosition();
	Point now = this->convertToWorldSpace(weapon_pos);
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
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), 0.7f, 0.7f);
	auto weapon_rotate_up = RotateBy::create(m_attack_speed / 2, -5);
	auto weapon_rotate_down = RotateBy::create(m_attack_speed / 2, 5);
	auto call_back = CallFunc::create(
		[&](){
		m_is_attack = false;
	}
	);
	if ((degree > 0 && dy < 0 && dx < 0) || (degree < 0 && dy>0 && dx < 0))
	{
		degree += 180;
		getSprite()->setFlippedX(true);
		auto gun_action = Sequence::create(weapon_rotate_down, weapon_rotate_up, call_back, NULL);
		m_sprite->runAction(gun_action);
	}
	else
	{
		getSprite()->setFlippedX(false);
		auto gun_action = Sequence::create(weapon_rotate_up, weapon_rotate_down, call_back, NULL);
		m_sprite->runAction(gun_action);
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

std::vector<Bullet*> LongRange::getBullet()const
{
	return m_bullet;
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