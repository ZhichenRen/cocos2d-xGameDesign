#include "Entity\Weapons\GoldenSword.h"

bool GoldenSword::init()
{
	m_damage = 20;
	m_range = 25;
	m_attack_speed = 0.2f;
	m_crit_rate = 0.2f;
	m_weaponName = "GoldenSword!";
	bindSprite(Sprite::create("GoldenSword!.png"), 0.16f, 0.16f);
	m_sprite->setAnchorPoint(Vec2(0, 0));
	return true;
}