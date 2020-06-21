#include "Entity\Weapons\Bullets\ExplosiveBullet.h"

bool ExplosiveBullet::init()
{
	if (!Bullet::init())
	{
		return false;
	}
	m_is_explode = false;
	return true;
}

void ExplosiveBullet::explosionCallback()
{
	m_is_used = true;
	m_is_explode = false;
}

void ExplosiveBullet::explode()
{
	this->stopAllActions();
	m_sprite->setVisible(false);
	auto explosion = ParticleMeteor::create();
	explosion->setEmitterMode(ParticleSystem::Mode::RADIUS);
	explosion->setPositionType(ParticleSystem::PositionType::RELATIVE);
	explosion->setAutoRemoveOnFinish(true);
	explosion->setTotalParticles(3000);
	explosion->setPosition(0, 0);
	explosion->setDuration(0.2f);
	explosion->setStartRadius(30.0f);
	explosion->setStartRadiusVar(20.0f);
	explosion->setEndRadius(0.0f);
	m_is_explode = true;
	this->addChild(explosion);

	auto callback = CallFunc::create(
		[this]() {
		this->explosionCallback();
	}
	);

	auto explode_action = Sequence::create(DelayTime::create(0.5f), callback, NULL);
	runAction(explode_action);
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

bool ExplosiveBullet::isExplode()const
{
	return m_is_explode;
}