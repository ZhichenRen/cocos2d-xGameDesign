#include "Entity\Weapons\MonsterSword.h"

bool MonsterSword::init()
{
	m_damage = 2;
	m_range = 20;
	m_attack_speed = 2.0f;
	bindSprite(Sprite::create("GoldenSword!.png"), 0.1f, 0.1f);
	//getSprite()->setVisible(false);
	return true;
}

void MonsterSword::setRange(int range)
{
	this->m_range = range;
}
