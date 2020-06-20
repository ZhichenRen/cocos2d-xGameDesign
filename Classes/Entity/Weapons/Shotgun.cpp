#include "Entity\Weapons\Shotgun.h"
#include "Entity\Weapons\Bullets\Bullet.h"
#define PI 3.1415926

bool Shotgun::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	m_power_cost = 5;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 5;
	m_bullet_speed = 600;
	m_attack_speed = 0.2f;
	m_degree = 15.0f;
	m_bullet_num_at_once = 4;
	m_crit_rate = 0.1f;
	m_weaponName = "Rifle&Shotgun";
	m_bullet_picture = std::string("BasicBullet.png");
	bindSprite(Sprite::create("Rifle&Shotgun.png"), 0.14f, 0.14f);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	return true;
}

void Shotgun::upgrade()
{
	isUpgrate = true;
	m_power_cost = 5;
	m_bullet_damage = 8;
	m_bullet_speed = 650;
	m_attack_speed = 0.18f;
	m_degree = 10.0f;
	m_bullet_num_at_once = 5;
	m_crit_rate = 0.15f;
	auto upgrade_effect = ParticleFlower::create();
	upgrade_effect->setEmitterMode(ParticleSystem::Mode::RADIUS);
	upgrade_effect->setPositionType(ParticleSystem::PositionType::RELATIVE);
	upgrade_effect->setAutoRemoveOnFinish(true);
	upgrade_effect->setTotalParticles(100);
	upgrade_effect->setPosition(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height / 2);
	upgrade_effect->setDuration(-1);
	upgrade_effect->setStartRadius(50.0f);
	upgrade_effect->setStartRadiusVar(25.0f);
	upgrade_effect->setEndRadius(50.0f);
	getSprite()->addChild(upgrade_effect);
}

void Shotgun::attack(Point pos)
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
	for (int i = 1; i <= m_bullet_num_at_once; i++)
	{
		float fire_degree;
		if (m_bullet_num_at_once % 2)
		{
			int mid = m_bullet_num_at_once / 2 + 1;
			fire_degree = degree - (i - mid) * m_degree;
		}
		else
		{
			int mid = m_bullet_num_at_once / 2;
			if (i <= mid)
			{
				fire_degree = degree - (i - mid) * m_degree + m_degree / 2;
			}
			else
			{
				fire_degree = degree - (i - mid - 1) * m_degree - m_degree / 2;
			}
		}
		auto new_bullet = generateBullet(degree, 0.3f, 0.3f);
		new_bullet->setBulletAction(fire_degree, m_bullet_speed);
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