#include "ChiefOfTribe.h"

bool ChiefOfTribe::init()
{
	m_fIsFacingRight = false;
	setMonsterSpeed(0.8f);
	setHp(this->m_initHp);
	setResTrack("chief_of_tribe.png");
	auto gun = MonsterGun::create();
	gun->setPosition(this->getPosition());
	setMonsterWeapon(gun);
	this->bindSprite(Sprite::create(this->getResTrack()), 0.8f, 0.8f);
	this->addChild(gun, 1);
	m_isAlive = true;
	return true;
}

void ChiefOfTribe::resetPropoties()
{
	show();
	setHp(this->m_initHp);
	m_isAlive = true;
}

