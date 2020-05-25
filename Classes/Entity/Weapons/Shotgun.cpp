#include "Entity\Weapons\Shotgun.h"
#include "Entity\Weapons\Bullets\Bullet.h"
#define PI 3.1415926

bool Shotgun::init()
{
	m_power_cost = 5;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 5;
	m_bullet_speed = 500;
	m_attack_speed = 0.25f;
	m_degree = 15.0f;
	m_bullet_num_at_once = 4;
	m_bullet_picture = std::string("BasicBullet.png");
	bindSprite(Sprite::create("Rifle&Shotgun.png"), 0.2f, 0.2f);
	return true;
}

void Shotgun::attack(Point pos)
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
	m_bullet_num -= m_bullet_num_at_once;
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
	auto weapon_rotate_up = RotateBy::create(m_attack_speed / 2, -5);
	auto weapon_rotate_down = RotateBy::create(m_attack_speed / 2, 5);
	auto call_back = CallFunc::create(
		[&]() {
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
	for (int i = 1; i <= m_bullet_num_at_once; i++)
	{
		Bullet* new_bullet = Bullet::create();
		new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), 0.5f, 0.5f);
		new_bullet->setInfo(m_range, m_bullet_damage);
		new_bullet->setPosition(getSprite()->getPositionX() + getSprite()->getBoundingBox().size.width*cos(degree / 180 * PI) / 2
			, getSprite()->getPositionY() + getSprite()->getBoundingBox().size.width*sin(degree / 180 * PI) / 2);
		new_bullet->setOriginPos(new_bullet->getPosition());
		float fire_degree;
		if (m_bullet_num_at_once % 2)
		{
			int mid = m_bullet_num_at_once / 2 + 1;
			fire_degree = degree - (i - mid)*m_degree;
		}
		else
		{
			int mid = m_bullet_num_at_once / 2;
			if (i <= mid)
			{
				fire_degree = degree - (i - mid)*m_degree + m_degree / 2;
			}
			else
			{
				fire_degree = degree - (i - mid - 1)*m_degree - m_degree / 2;
			}
		}
		new_bullet->setRotation(-fire_degree);
		new_bullet->setVisible(true);
		this->addChild(new_bullet);
		auto move_action = MoveBy::create(1.0f, Vec2(m_bullet_speed*cos(fire_degree / 180 * PI), m_bullet_speed*sin(fire_degree / 180 * PI)));
		auto attack_action = RepeatForever::create(move_action);
		new_bullet->runAction(attack_action);
		m_bullet.push_back(new_bullet);
	}
}

void Shotgun::setBulletDegree(float new_degree)
{
	m_degree = new_degree;
}

void Shotgun::setBulletNumAtOnce(int new_num)
{
	m_bullet_num_at_once = new_num;
}

float Shotgun::getBulletDegree()const
{
	return m_degree;
}

int Shotgun::getBulletNumAtOnce()const
{
	return m_bullet_num_at_once;
}