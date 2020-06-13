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
	m_bullet_damage = 4;
	m_bullet_speed = 500;
	m_attack_speed = 0.15f;
	m_crit_rate = 0.1f;
	m_weaponName = "Pistol";
	m_bullet_picture = std::string("BasicBullet.png");
	bindSprite(Sprite::create("Pistol.png"), 0.15f, 0.15f);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	return true;
}