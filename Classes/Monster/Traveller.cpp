#include "Traveller.h"

bool Traveller::init()
{
	m_fIsFacingRight = false;
	setMonsterSpeed(1.5);
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg);
	setHp(this->m_initHp);
	setResTrack("traveller.png");
	this->bindSprite(Sprite::create(this->getResTrack()), 1.0f, 1.0f);
	auto sword = MonsterSword::create();
	auto swordSize = sword->getContentSize();
	sword->setContentSize(swordSize * 2);
	sword->getSprite()->setContentSize(sword->getSprite()->getContentSize() * 3);
	sword->setRange(sword->getRange() * 3);
	sword->setDamage(3);
	sword->setAttackSpeed(1.5f);
	//sword->setPosition(this->getPosition());
	setMonsterWeapon(sword);
	this->addChild(sword, 1);
	m_isAlive = true;
	return true;
}
void Traveller::resetPropoties()
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