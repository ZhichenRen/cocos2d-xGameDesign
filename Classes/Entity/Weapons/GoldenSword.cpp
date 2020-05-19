#include "Entity\Weapons\GoldenSword.h"

bool GoldenSword::init()
{
	m_damage = 100;
	m_range = 30;
	m_attack_speed = 0.3f;
	bindSprite(Sprite::create("GoldenSword!.png"), 0.2f, 0.2f);
	m_sprite->setAnchorPoint(Vec2(0, 0));
	return true;
}

