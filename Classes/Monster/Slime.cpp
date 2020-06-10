#include "Slime.h"

bool Slime::init()
{
	m_fIsFacingRight = false;
	setMonsterSpeed(0.2);
	setHp(this->m_initHp);
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg);
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

