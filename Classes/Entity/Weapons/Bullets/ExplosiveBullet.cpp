#include "Entity\Weapons\Bullets\ExplosiveBullet.h"

bool ExplosiveBullet::init()
{
	if (!Bullet::init())
	{
		return false;
	}
	return true;
}

void ExplosiveBullet::explode()
{
	this->stopAllActions();
	m_sprite->setVisible(false);
	m_is_used = true;
	auto explosion = ParticleMeteor::create();
	explosion->setEmitterMode(ParticleSystem::Mode::RADIUS);
	explosion->setPositionType(ParticleSystem::PositionType::RELATIVE);
	explosion->setTotalParticles(3000);
	explosion->setPosition(0, 0);
	explosion->setDuration(0.2f);
	explosion->setStartRadius(30.0f);
	explosion->setStartRadiusVar(20.0f);
	explosion->setEndRadius(0.0f);
	this->addChild(explosion);
}

void ExplosiveBullet::setInfo(int range, int damage, int explosion_range, int explosion_damage)
{
	m_bullet_range = range;
	m_bullet_damage = damage;
	m_explosion_range = explosion_range;
	m_explosion_damage = explosion_damage;
}

int ExplosiveBullet::getExplosionDamage()const
{
	return m_explosion_damage;
}

int ExplosiveBullet::getExplosionRange()const
{
	return m_explosion_range;
}