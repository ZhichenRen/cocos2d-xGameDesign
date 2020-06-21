#include "duck.h"
#include "Entity/Weapons/TrackWeapon.h"

bool Duck::init()
{
	m_fIsFacingRight = false;
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg);

	setMonsterSpeed(0.5);
	setHp(this->m_initHp);
	setResTrack("duck.png");
	this->bindSprite(Sprite::create(this->getResTrack()), 0.8f, 0.8f);

	auto gun = TrackWeapon::create();
	gun->setPosition(this->getPosition());
	setMonsterWeapon(gun);
	this->addChild(gun, 1);

	m_isAlive = true;
	return true;
}

void Duck::resetPropoties()
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

//void Duck::resetPropoties()
//{
//	show();
//	setHp(this->m_initHp);
//	m_fIsTaunted = 0;
//	m_isAlive = true;
//}