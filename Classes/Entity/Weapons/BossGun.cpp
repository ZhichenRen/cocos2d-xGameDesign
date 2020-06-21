#include "Entity/Weapons/BossGun.h"

bool BossGun::init()
{
	if (!Shotgun::init())
	{
		return false;
	}
	m_bullet_damage = 3;
	m_bullet_speed = 250;
	m_attack_speed = 1.0f;
	m_bullet_num_at_once = 9;
	m_degree = 40.0f;
	m_bullet_picture = std::string("BossBullet.png");
	getSprite()->setVisible(false);
	return true;
}