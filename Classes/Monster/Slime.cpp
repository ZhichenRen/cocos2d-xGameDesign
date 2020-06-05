#include "Slime.h"

bool Slime::init()
{
	setMonsterSpeed(0.2);
	setHp(50);
	setResTrack("Slime.png"); 
	auto gun = MonsterGun::create();
	gun->setPosition(this->getPosition());
	setMonsterWeapon(gun);
	this->bindSprite(Sprite::create(this->getResTrack()), 1.2f, 1.2f);
	this->addChild(gun, 1);
	m_isAlive = true;
	return true;
}

void Slime::resetPropoties()
{
	show();
	setHp(150);
	m_isAlive = true;
}

