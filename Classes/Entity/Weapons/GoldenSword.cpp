#include "Entity\Weapons\GoldenSword.h"

bool GoldenSword::init()
{
	m_damage = 30;
	m_range = 40;
	m_attack_speed = 0.2f;
	m_crit_rate = 0.2f;
	bindSprite(Sprite::create("GoldenSword!.png"), 0.2f, 0.2f);
	m_sprite->setAnchorPoint(Vec2(0, 0));
	return true;
}

