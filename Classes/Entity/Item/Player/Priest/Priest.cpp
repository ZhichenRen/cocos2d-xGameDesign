#include "Entity/Item/Player/Priest/Priest.h"

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
	m_iNowSkillDuration = 180;
	m_iTotalSkillDuration = 180;
	m_numTotalWeapon = 3;
	m_numWeapon = 0;
	m_numLongRange = 0;
	m_isInSkill = false;

	m_skillTime = 0;
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
	m_map->addChild(sprite);
	sprite->setPosition(getPosition());
	m_priestSkill = sprite;
}

void Priest::skillDuration()
{

}

void Priest::skillEnd()
{
	m_isInSkill = false;
	m_priestSkill->removeFromParent();
}

void Priest::die()
{
	
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
