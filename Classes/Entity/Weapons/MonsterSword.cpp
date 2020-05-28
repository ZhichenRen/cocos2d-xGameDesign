#include "Entity\Weapons\MonsterSword.h"

bool MonsterSword::init()
{
	m_damage = 50;
	m_range = 20;
	m_attack_speed = 3.0f;
	bindSprite(Sprite::create("GoldenSword!.png"), 0.2f, 0.2f);
	//this->getSprite()->setVisible(false);
	return true;
}