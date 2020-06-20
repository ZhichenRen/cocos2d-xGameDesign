#include "Entity\Weapons\LongRange.h"
#include "Entity\Weapons\Bullets\ExplosiveBullet.h"
#include <cmath>
#define PI 3.1415926

LongRange::LongRange()
{
}

bool LongRange::init()
{
	if (!Weapon::init())
	{
		return false;
	}
	m_bullet_speed = 1;
	m_attack_speed = 0.4f;
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
	Point weapon_pos = getPosition();
	Point now = getParent()->convertToWorldSpace(weapon_pos);
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

bool LongRange::isAttacking()
{
	return m_is_attack;
}

void LongRange::setRotationByPos(Point pos)
{
	auto now = getParent()->convertToWorldSpace(getPosition());
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
	if ((degree > 0 && dy < 0 && dx < 0) || (degree < 0 && dy>0 && dx < 0))
	{
		getSprite()->setFlippedX(true);
		getSprite()->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else
	{
		getSprite()->setFlippedX(false);
		getSprite()->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
}

std::vector<Bullet*> LongRange::getBullet()const
{
	return m_bullet;
}

int LongRange::getDamage()const
{
	return m_bullet_damage;
}

void LongRange::setDamage(int damage)
{
	m_bullet_damage = damage;
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
			(*it)->removeFromParentAndCleanup(true);
			it = m_bullet.erase(it);
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
	auto call_back = CallFunc::create(
		[&]() {
		m_is_attack = false;
	}
	);
	if (is_flipped)
	{
		getSprite()->setFlippedX(true);
		getSprite()->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else
	{
		getSprite()->setFlippedX(false);
		getSprite()->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
	auto gun_action = Sequence::create(DelayTime::create(m_attack_speed), call_back, NULL);
	m_sprite->runAction(gun_action);
}

Bullet* LongRange::generateBullet(float degree, float scale_x, float scale_y)
{
	Bullet* new_bullet = Bullet::create();
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), scale_x, scale_y);
	new_bullet->setInfo(m_range, m_bullet_damage);
	new_bullet->setCritRate(m_crit_rate);
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

void LongRange::flipped(bool status)
{
	if (status == true)//toward left
	{
		getSprite()->setFlippedX(true);
		getSprite()->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else
	{
		getSprite()->setFlippedX(false);
		getSprite()->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
}

bool LongRange::isCloseWeapon()const
{
	return false;
}

LongRange::~LongRange()
{

}