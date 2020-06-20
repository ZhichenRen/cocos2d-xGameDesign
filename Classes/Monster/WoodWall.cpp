#include "Monster/WoodWall.h"

bool WoodWall::init()
{
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg);
	setHp(this->m_initHp);
	setResTrack("WoodWall.png");
	this->bindSprite(Sprite::create(this->getResTrack()));
	m_isAlive = true;
	return true;
}

void WoodWall::hit(int damage, float flyingDegree, bool isCriticalStrike)
{
	if (!m_isAlive)
		return;
	this->m_Hp -= damage;

	if (isCriticalStrike)
	{
		std::string msg = std::to_string(damage) + '!';
		m_damageMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2);
		return;
	}
	std::string msg = std::to_string(damage);
	m_damageMsg->showMonsDmg(msg.c_str(), this->getContentSize().height / 2);
}
