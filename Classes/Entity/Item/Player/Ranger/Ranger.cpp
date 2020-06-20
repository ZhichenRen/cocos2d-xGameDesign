#include "Entity/Item/Player/Ranger/Ranger.h"
#include "Entity/Weapons/CloseWeapon.h"
#include "Entity/Weapons/LongRange.h"
Ranger::Ranger()
{

}

Ranger::~Ranger()
{

}

bool Ranger::init()
{
	auto sprite = Sprite::create("Ranger/RangerIni.png");
	bindSprite(sprite, 1.05, 1.05);
	m_iNowHp = 5;
	m_iTotalHp = 5;
	m_iNowMp = 180;
	m_iTotalMp = 180;
	m_iNowCD = 150;
	m_iTotalCD = 150;
	m_iArmorCd = 0;
	m_iNowArmor = 3;
	m_iTotalArmor = 3;
	m_iNowSkillDuration = 1;
	m_iTotalSkillDuration = 1;
	m_numTotalWeapon = 3;
	m_numWeapon = 0;
	m_numHasWeapon = 0;
	m_numLongRange = 0;
	m_isInSkill = false;
	m_shield = Sprite::create("shield1.png");
	m_shield->setPosition(0, 0);
	m_shield->setVisible(false);
	this->addChild(m_shield, 5);
	return true;
}


Animate* Ranger::walk()
{
	if (getSprite() == NULL)
	{
		return NULL;
	}
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Ranger/RangerWalk/", "RangerWalk", 4, 0.12, -1);
	auto animate = Animate::create(animation);
	m_sprite->runAction(animate);
	return animate;
}

void Ranger::skill()
{
	if (getSprite() == NULL || getiNowCD() < getiTotalCD())
	{
		return;
	}
	setiNowSkillDuration(0);
	m_isInSkill = true;
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Ranger/RangerSkill/", "RangerSkill", 4, 0.08, 1);
	auto animate = Animate::create(animation);
	stopAllActions();
	m_sprite->runAction(animate);

	setiNowCD(0);
}

void Ranger::skillEnd()
{
	m_isInSkill = false;
	m_skillDirectionX = 0;
	m_skillDirectionY = 0;
}

void Ranger::die()
{
	m_isDeath = true;
	auto m_addBloodMsg = FlowWord::create();
	this->addChild(m_addBloodMsg);
	std::string msg = "Revive!";
	m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
	getSprite()->setOpacity(0);
}

Animate* Ranger::stand()
{
	if (getSprite() == NULL)
	{
		return NULL;
	}
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Ranger/RangerStand/", "RangerStand", 4, 0.12, -1);
	auto animate = Animate::create(animation);
	m_sprite->runAction(animate);
	return animate;
}

Point Ranger::getSkillDirection()
{
	if (m_controller->getiXSpeed() == 0 && m_controller->getiYSpeed() == 0)
	{
		m_skillDirectionX = 1;
		m_skillDirectionY = 0;
		return Point(100, 0);
	}
	else if (m_controller->getiXSpeed() == 0 || m_controller->getiYSpeed() == 0)
	{
		m_skillDirectionX = isPositiveOrNegative(m_controller->getiXSpeed());
		m_skillDirectionY = isPositiveOrNegative(m_controller->getiYSpeed());
		return Point(isPositiveOrNegative(m_controller->getiXSpeed()) * 100
			, isPositiveOrNegative(m_controller->getiYSpeed()) * 100);
	}
	else
	{
		m_skillDirectionX = isPositiveOrNegative(m_controller->getiXSpeed());
		m_skillDirectionY = isPositiveOrNegative(m_controller->getiYSpeed());
		return Point(isPositiveOrNegative(m_controller->getiXSpeed()) * 71
			, isPositiveOrNegative(m_controller->getiYSpeed()) * 71);
	}
	m_skillDirectionX = 1;
	m_skillDirectionY = 0;
	return Point(100, 0);
}