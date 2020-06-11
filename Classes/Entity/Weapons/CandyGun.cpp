#include "Entity\Weapons\CandyGun.h"

CandyGun::CandyGun()
{

}

bool CandyGun::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	m_power_cost = 3;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 10;
	m_bullet_speed = 600;
	m_attack_speed = 0.12f;
	m_crit_rate = 0.3f;
	m_bullet_picture = std::string("CandyBullet.png");
	bindSprite(Sprite::create("CandyGun!.png"), 0.25f, 0.25f);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));

	//test
	auto upgrade_effect = ParticleFlower::create();
	upgrade_effect->setEmitterMode(ParticleSystem::Mode::RADIUS);
	upgrade_effect->setPositionType(ParticleSystem::PositionType::RELATIVE);
	upgrade_effect->setAutoRemoveOnFinish(true);
	upgrade_effect->setTotalParticles(10);
	upgrade_effect->setPosition(0, 0);
	upgrade_effect->setDuration(-1);
	upgrade_effect->setStartRadius(12.0f);
	upgrade_effect->setStartRadiusVar(6.0f);
	upgrade_effect->setEndRadius(0.0f);
	addChild(upgrade_effect);

	return true;
}

void CandyGun::upgrade()
{
	m_power_cost = 3;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 20;
	m_bullet_speed = 750;
	m_attack_speed = 0.1f;
	m_crit_rate = 0.5f;
	auto upgrade_effect = ParticleFlower::create();
	upgrade_effect->setEmitterMode(ParticleSystem::Mode::RADIUS);
	upgrade_effect->setPositionType(ParticleSystem::PositionType::RELATIVE);
	upgrade_effect->setAutoRemoveOnFinish(true);
	upgrade_effect->setTotalParticles(10);
	upgrade_effect->setPosition(0, 0);
	upgrade_effect->setDuration(-1);
	upgrade_effect->setStartRadius(12.0f);
	upgrade_effect->setStartRadiusVar(6.0f);
	upgrade_effect->setEndRadius(0.0f);
	addChild(upgrade_effect);
}

CandyGun::~CandyGun()
{

}