#include "Entity\Weapons\RPG.h"

#define PI 3.1415926

bool RPG::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	scheduleUpdate();
	m_power_cost = 5;
	m_bullet_num = 30;
	m_range = 250;
	m_bullet_damage = 5;
	m_bullet_speed = 300;
	m_attack_speed = 0.3f;
	m_explosion_damage = 2;
	m_explosion_range = 30;
	m_crit_rate = 0.0f;
	m_bullet_picture = std::string("RPG.png");
	m_weaponName = "Fist_of_Heaven";
	bindSprite(Sprite::create("Fist_of_Heaven.png"), 0.15f, 0.15f);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	scheduleUpdate();
	return true;
}

void RPG::upgrade()
{
	isUpgrate = true;
	m_power_cost = 4;
	m_bullet_damage = 5;
	m_bullet_speed = 350;
	m_attack_speed = 0.25f;
	m_explosion_damage = 3;
	m_explosion_range = 40;
	m_crit_rate = 0.0f;
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

void RPG::attack(Point pos)
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
	ExplosiveBullet* new_bullet = generateExplosiveBullet(degree, 0.3f, 0.3f);
	new_bullet->setBulletAction(degree, m_bullet_speed);
}

ExplosiveBullet* RPG::generateExplosiveBullet(float degree, float scale_x, float scale_y)
{
	ExplosiveBullet* new_bullet = ExplosiveBullet::create();
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), scale_x, scale_y);
	new_bullet->setInfo(m_range, m_bullet_damage, m_explosion_range, m_explosion_damage);
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