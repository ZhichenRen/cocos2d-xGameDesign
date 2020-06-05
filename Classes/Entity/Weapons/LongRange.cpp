#include "Entity\Weapons\LongRange.h"
#include "Entity\Weapons\Bullets\ExplosiveBullet.h"
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
	scheduleUpdate();
	return true;
}

void LongRange::attack(Point pos)
{
	if (m_is_attack == true)
	{
		return;
	}
	m_is_attack = true;
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

	if ((degree > 0 && dy < 0 && dx < 0) || (degree < 0 && dy>0 && dx < 0))
	{
		adjustWeaponPosition(degree, true);
		degree += 180;
	}
	else
	{
		adjustWeaponPosition(degree, false);
	}
	auto new_bullet = generateBullet(degree, 0.3f, 0.3f);
	new_bullet->setBulletAction(degree, m_bullet_speed);
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
	//for (auto bullet : m_bullet)
	//{
	//	if (bullet->getDistance() > m_range)
	//	{
	//		if (typeid(*bullet) == typeid(ExplosiveBullet))
	//		{
	//			dynamic_cast<ExplosiveBullet*>(bullet)->explode();
	//		}
	//		bullet->setIsUsed(true);
	//	}
	//}
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

void LongRange::adjustWeaponPosition(float degree, bool is_flipped)
{
	getSprite()->setRotation(-degree);
	Bullet* new_bullet = Bullet::create();
	auto weapon_rotate_up = RotateBy::create(m_attack_speed / 2, -5);
	auto weapon_rotate_down = RotateBy::create(m_attack_speed / 2, 5);
	auto call_back = CallFunc::create(
		[&]() {
		m_is_attack = false;
	}
	);
	if (is_flipped)
	{
		getSprite()->setFlippedX(true);
		getSprite()->setAnchorPoint(Vec2(1.0f, 0.5f));
		auto gun_action = Sequence::create(weapon_rotate_down, weapon_rotate_up, call_back, NULL);
		m_sprite->runAction(gun_action);
	}
	else
	{
		getSprite()->setFlippedX(false);
		getSprite()->setAnchorPoint(Vec2(0.0f, 0.5f));
		auto gun_action = Sequence::create(weapon_rotate_up, weapon_rotate_down, call_back, NULL);
		m_sprite->runAction(gun_action);
	}
}

Bullet* LongRange::generateBullet(float degree, float scale_x, float scale_y)
{
	Bullet* new_bullet = Bullet::create();
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), scale_x, scale_y);
	new_bullet->setInfo(m_range, m_bullet_damage);
	Point origin_pos = Point(getSprite()->getPositionX() + getSprite()->getBoundingBox().size.width * cos(degree / 180 * PI)
		, getSprite()->getPositionY() + getSprite()->getBoundingBox().size.width * sin(degree / 180 * PI));
	origin_pos = m_map->convertToMapSpace(convertToWorldSpace(origin_pos));
	new_bullet->setPosition(origin_pos);
	new_bullet->setOriginPos(origin_pos);
	new_bullet->setRotation(-degree);
	new_bullet->setVisible(true);
	m_map->addChild(new_bullet, 2);
	m_bullet.push_back(new_bullet);
	return new_bullet;
}

LongRange::~LongRange()
{

}