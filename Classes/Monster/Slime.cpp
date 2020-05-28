#include "Slime.h"

bool Slime::init()
{
	setMonsterSpeed(0.1);
	setHp(150);
	setResTrack("Slime.png"); 
	auto gun = MonsterGun::create();
	gun->setPosition(this->getPosition());
	setMonsterWeapon(gun);

	this->bindSprite(Sprite::create(this->getResTrack()), 0.8f, 0.8f);
	this->addChild(gun, 1);
	m_isAlive = true;
	return true;
}

