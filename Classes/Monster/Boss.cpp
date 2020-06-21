
#include "Monster/Boss.h"
#include "Monster/Monster.h"
#include "Entity/Weapons/BossGun.h"
bool Boss::init()
{
	m_fIsFacingRight = false;
	m_damageMsg = FlowWord::create();
	this->addChild(m_damageMsg,2);

	setMonsterSpeed(0.8f);
	setHp(this->m_initHp);
	setResTrack("Boss.png");
	auto gun = BossGun::create();
	gun->setPosition(this->getPosition());
	setMonsterWeapon(gun);
	//gun->setDamage(2);
	gun->setAttackSpeed(1.5f);
	this->bindSprite(Sprite::create(this->getResTrack()));
	this->addChild(gun, 1);
	m_isAlive = true;
	return true;
}




void Boss::hit(int damage, float flyingDegree, bool isCriticalStrike)
{
	if (!m_isAlive)
		return;
	this->m_Hp -= damage;
	setMonsTaunted();
	this->stopAllActions();
	/*if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(targetPos))))
	{
		auto move_action = MoveBy::create(0.1f, vecToMove);

		this->runAction(move_action);
	}*/
	if (isCriticalStrike)
	{
		std::string msg = std::to_string(damage) + '!';
		m_damageMsg->showCritDmg(msg.c_str(), 200);

		return;
	}

	std::string msg = std::to_string(damage);
	m_damageMsg->showMonsDmg(msg.c_str(), 200);
}

