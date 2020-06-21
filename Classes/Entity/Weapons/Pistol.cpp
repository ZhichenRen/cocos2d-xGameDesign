
#include "Entity/Weapons/Pistol.h"

bool Pistol::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	m_power_cost = 1;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 5;
	m_bullet_speed = 400;
	m_attack_speed = 0.15f;
	m_crit_rate = 0.1f;
	m_weaponName = "Pistol";
	m_bullet_picture = std::string("BasicBullet.png");
	bindSprite(Sprite::create("Pistol.png"), 0.15f, 0.15f);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	return true;
}

void Pistol::upgrade()
{
	isUpgrate = true;
	m_power_cost = 0;
	m_bullet_damage = 5;
	m_bullet_speed = 500;
	m_attack_speed = 0.12f;
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