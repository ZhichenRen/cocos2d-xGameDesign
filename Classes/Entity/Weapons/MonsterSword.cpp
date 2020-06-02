#include "Entity\Weapons\MonsterSword.h"

bool MonsterSword::init()
{
	m_damage = 50;
	m_range = 20;
	m_attack_speed = 1.0f;
	bindSprite(Sprite::create("GoldenSword!.png"), 0.1f, 0.1f);
	return true;
}