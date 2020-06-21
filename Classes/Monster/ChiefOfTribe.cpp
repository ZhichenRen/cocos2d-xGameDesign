#include "ChiefOfTribe.h"

bool ChiefOfTribe::init()
{
	m_fIsFacingRight = false;
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg);
	setMonsterSpeed(0.8f);
	setHp(this->m_initHp);
	setResTrack("chief_of_tribe.png");
	auto gun = MonsterGun::create();
	gun->setPosition(this->getPosition());
	setMonsterWeapon(gun);
	gun->setDamage(2);
	gun->setAttackSpeed(1.5f);
	this->bindSprite(Sprite::create(this->getResTrack()), 0.8f, 0.8f);
	this->addChild(gun, 1);
	m_isAlive = true;
	return true;
}

void ChiefOfTribe::resetPropoties()
{
	m_isAlive = true;
	show();
	setHp(this->m_initHp);
	m_fIsTaunted = 0;
	if (m_isBulkUp)
	{
		setContentSize(Size(getContentSize().width / 2, getContentSize().height / 2));
		getSprite()->setContentSize(Size(getSprite()->getContentSize().width / 2, getSprite()->getContentSize().height / 2));
		m_isBulkUp = 0;
		m_fSpeed /= 1.3;
	}
}