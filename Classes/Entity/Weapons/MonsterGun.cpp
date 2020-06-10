#include "Entity\Weapons\MonsterGun.h"

MonsterGun::MonsterGun()
{
}

MonsterGun::~MonsterGun()
{
}

bool MonsterGun::init()
{
	m_power_cost = 0;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 1;
	m_bullet_speed = 100;
	m_attack_speed = 2.0f;
	m_bullet_picture = std::string("MonsterBullet.png");
	bindSprite(Sprite::create("MonsterBullet.png"), 0.6f, 0.6f);
	this->getSprite()->setVisible(false);
	return true;
}
