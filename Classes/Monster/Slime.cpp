#include "Slime.h"

bool Slime::init()
{
	setMonsterSpeed(0.1);
	setHp(150);
	setResTrack("Slime.png"); 
	auto gun = MonsterGun::create();
	gun->setPosition(this->getPosition());
	gun->setContentSize(Size(0.1, 0.1));
	setMonsterWeapon(gun);
	this->addChild(gun, 1);
	m_isAlive = true;
	return true;
}

