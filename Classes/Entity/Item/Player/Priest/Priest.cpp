#include "Entity/Item/Player/Priest/Priest.h"
#include "Scene/DeathScene.h"
#include "Entity/Weapons/CloseWeapon.h"
#include "Entity/Weapons/LongRange.h"

Priest::Priest()
{

}

Priest::~Priest()
{

}

bool Priest::init()
{
	auto sprite = Sprite::create("Priest/PriestIni.png");
	bindSprite(sprite, 0.42, 0.4);
	m_iNowHp = 4;
	m_iTotalHp = 4;
	m_iNowMp = 220;
	m_iTotalMp = 220;
	m_iNowCD = 600;
	m_iTotalCD = 600;
	m_iArmorCd = 0;
	m_iNowArmor = 5;
	m_iTotalArmor = 5;
	m_iNowSkillDuration = 200;
	m_iTotalSkillDuration = 200;
	m_numTotalWeapon = 3;
	m_numWeapon = 0;
	m_numHasWeapon = 0;
	m_numLongRange = 0;
	m_isInSkill = false;
	m_skillDirectionX = 0;
	m_skillDirectionY = 0;
	m_skillTime = 0;
	m_shield = Sprite::create("shield1.png");
	m_shield->setPosition(0, 0);
	m_shield->setVisible(false);
	this->addChild(m_shield,5);
	return true;
}


Animate* Priest::walk()
{
	/*if (getSprite() == NULL)
	{
		return NULL;
	}
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Priest/PriestWalk/", "PriestWalk", 4, 0.12, -1);
	auto animate = Animate::create(animation);
	m_sprite->runAction(animate);*/
	Animate* animate = NULL;
	return animate;
}

void Priest::skill()
{
	if (getSprite() == NULL || getiNowCD() < getiTotalCD())
	{
		return;
	}
	setiNowSkillDuration(0);
	m_isInSkill = true;
	setiNowCD(0);
	auto sprite = Sprite::create("Priest/PriestSkill/PriestSkill.png");
	sprite->setPosition(getPosition());
	Size size = sprite->getBoundingBox().size;
	sprite->setContentSize(size);
	m_priestSkill = sprite;
	m_map->addChild(m_priestSkill);
}

void Priest::skillDuration()
{
	if (m_priestSkill == NULL)
		return;
	if (ccpDistance(getPosition(), m_priestSkill->getPosition()) < 90.0f)
	{
		if (m_skillTime < 80)
		{
			m_skillTime++;
			return;
		}
		else
		{
			m_skillTime = 0;
			setiNowHp(getiNowHp() + 2);
			auto m_addBloodMsg = FlowWord::create();
			this->addChild(m_addBloodMsg);
			std::string msg = "+2";
			m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2);
		}
	}
	else
		m_skillTime = 0;
}

void Priest::skillEnd()
{
	m_isInSkill = false;
	m_skillTime = 0;
	m_priestSkill->removeFromParent();
}

void Priest::die()
{
	m_isDeath = true;
	auto m_addBloodMsg = FlowWord::create();
	this->addChild(m_addBloodMsg);
	std::string msg = "Revive!";
	m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
	getSprite()->setOpacity(0);
}

Animate* Priest::stand()
{

	/*if (getSprite() == NULL)
	{
		return NULL;
	}
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Priest/PriestStand/", "PriestStand", 4, 0.12, -1);
	auto animate = Animate::create(animation);
	m_sprite->runAction(animate);*/
	Animate* animate = NULL;
	return animate;
}
