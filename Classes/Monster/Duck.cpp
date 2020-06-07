#include "duck.h"

bool Duck::init()
{
	m_fIsFacingRight = false;
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg);
	setMonsterSpeed(0.5);
	setHp(this->m_initHp);
	setResTrack("duck.png");
	this->bindSprite(Sprite::create(this->getResTrack()), 0.8f, 0.8f);
	auto sword = MonsterSword::create();
	sword->setVisible(false);
	//sword->setPosition(this->getPosition());
	setMonsterWeapon(sword);
	this->addChild(sword, 1);
	m_isAlive = true;
	return true;
}

void Duck::resetPropoties()
{
	show();
	setHp(this->m_initHp);
	m_isAlive = true;
}