#include "Entity/Item/Player/Knight/Knight.h"
#include "Scene/DeathScene.h"
#include "Entity/Weapons/CloseWeapon.h"
#include "Entity/Weapons/LongRange.h"
#include "Entity/Item/Player/Player.h"
#include "Scene/TollgateScene.h"
#include "Entity\Weapons\Shotgun.h"
#include "Entity\Weapons\RPG.h"
#include "Entity\Weapons\GoldenSword.h"
#include "Entity\Weapons\CandyGun.h"
#include "Entity/Weapons/TrackWeapon.h"
#include "Entity/Weapons/Pistol.h"
#include "Entity/Weapons/StoneSword.h"

Knight::Knight()
{

}

Knight::~Knight()
{

}

bool Knight::init()
{
	auto sprite = Sprite::create("Knight/KnightIni.png");
	bindSprite(sprite, 1.0f, 1.0f);
	m_iNowHp = 6;
	m_iTotalHp = 6;
	m_iNowMp = 180;
	m_iTotalMp = 180;
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
	m_shield = Sprite::create("shield1.png");
	m_shield->setPosition(0, 0);
	m_shield->setVisible(false);
	this->addChild(m_shield, 5);
	return true;
}


Animate* Knight::walk()
{
	/*if (getSprite() == NULL)
	{
		return NULL;
	}
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Knight/KnightWalk/", "KnightWalk", 4, 0.12, -1);
	auto animate = Animate::create(animation);
	m_sprite->runAction(animate);*/
	Animate* animate = NULL;
	return animate;
}

void Knight::skill()
{
	if (getSprite() == NULL || getiNowCD() < getiTotalCD())
	{
		return;
	}
	setiNowSkillDuration(0);
	m_isInSkill = true;
	m_isKightSkill = true;
	setiNowCD(0);
	skillChooseWeapon();
	determineSkillWeapon();
}

void Knight::skillChooseWeapon()
{
	if (m_weapons[m_numWeapon - 1] == "CandyGun!")
	{
		m_skillClose = NULL;
		m_skillLongRange = CandyGun::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_skillLongRange->upgrade();
		loadSkillLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "GoldenSword!")
	{
		m_skillLongRange = NULL;
		m_skillClose = GoldenSword::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_skillClose->upgrade();
		loadSkillCloseWeaponListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "Fist_of_Heaven")
	{
		m_skillClose = NULL;
		m_skillLongRange = RPG::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_skillLongRange->upgrade();
		loadSkillLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "Rifle&Shotgun")
	{
		m_skillClose = NULL;
		m_skillLongRange = Shotgun::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_skillLongRange->upgrade();
		loadSkillLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "Pistol")
	{
		m_skillClose = NULL;
		m_skillLongRange = Pistol::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_skillLongRange->upgrade();
		loadSkillLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "StoneSword")
	{
		m_skillLongRange = NULL;
		m_skillClose = StoneSword::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_skillClose->upgrade();
		loadSkillCloseWeaponListener();
	}
}

void Knight::skillDuration()
{

}

void Knight::skillEnd()
{
	m_isInSkill = false;
	m_isKightSkill = false;
	removeSkill();
	m_skillDirectionX = 0;
	m_skillDirectionY = 0;
}

void Knight::die()
{
	m_isDeath = true;
	auto m_addBloodMsg = FlowWord::create();
	this->addChild(m_addBloodMsg);
	std::string msg = "Revive!";
	m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
	getSprite()->setOpacity(0);
}

Animate* Knight::stand()
{

	/*if (getSprite() == NULL)
	{
		return NULL;
	}
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Knight/KnightStand/", "KnightStand", 4, 0.12, -1);
	auto animate = Animate::create(animation);
	m_sprite->runAction(animate);*/
	Animate* animate = NULL;
	return animate;
}


void Knight::loadSkillLongRangeListener()
{
	m_numLongRange++;
	LongRange* longRange = m_skillLongRange;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = [longRange, this](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());

		if (m_iNowMp >= longRange->getPowerCost())
		{
			m_is_attacking = true;

			//call back to change attack status
			auto attack_delay = DelayTime::create(longRange->getAttackSpeed());
			auto callback = CallFunc::create(
				[this]() {
				m_is_attacking = false;
			}
			);
			auto attack = Sequence::create(attack_delay, callback, NULL);
			this->runAction(attack);
			longRange->attack(pos);
			//this->hit(2);
			this->mpDepletion(longRange->getPowerCost());
		}
		if (pos.x < 1024 / 2)//屏幕一半大小
		{
			setRightToward();
		}
		else
		{
			setLeftToward();
		}
	};
	m_skillListener = listener;
	m_longRanges[findWhichLongRange()] = longRange;

	auto mouse_move = EventListenerMouse::create();
	mouse_move->onMouseMove = [longRange, this](Event* event)
	{
		if (longRange == NULL)
		{
			return;
		}
		EventMouse* mouse = dynamic_cast<EventMouse*>(event);
		auto pos = Point(mouse->getCursorX(), mouse->getCursorY());
		longRange->setRotationByPos(pos);
		if (pos.x < 1024 / 2)//屏幕一半大小
		{
			setRightToward();
		}
		else
		{
			setLeftToward();
		}
	};
	m_skillMouseMove = mouse_move;
}

void Knight::loadSkillCloseWeaponListener()
{
	CloseWeapon* closeWeapon = m_skillClose;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = [closeWeapon, this](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (m_iNowMp >= closeWeapon->getPowerCost())
		{
			m_is_attacking = true;

			//call back to change attack status
			auto attack_delay = DelayTime::create(closeWeapon->getAttackSpeed());
			auto callback = CallFunc::create(

				[this]() {
				m_is_attacking = false;
			}
			);
			auto attack = Sequence::create(attack_delay, callback, NULL);
			this->runAction(attack);
			closeWeapon->attack(pos);
			//this->hit(2);
			this->mpDepletion(closeWeapon->getPowerCost());
		}
		if (pos.x < 1024 / 2)//屏幕一半大小
		{
			setRightToward();
		}
		else
		{
			setLeftToward();
		}
	};
	m_skillListener = listener;
}

void Knight::determineSkillWeapon()
{
	if (m_longRange != NULL && m_close == NULL)
	{
		if(m_longRange->getPosition().x==15)
		    m_skillLongRange->setPosition(-15, -5);
		else
			m_skillLongRange->setPosition(15, -5);
		m_skillLongRange->bindMap(m_map);
		this->addChild(m_skillLongRange);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_skillListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_skillMouseMove, this);
	}
	else
	{
		if (m_close->getPosition().x == 15)
		    m_skillClose->setPosition(-15, -9);
		else
			m_skillClose->setPosition(15, -9);
		m_skillClose->bindMap(m_map);
		this->addChild(m_skillClose);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_skillListener, this);
	}

}

void Knight::removeSkill()
{
	if (m_skillLongRange == NULL && m_skillClose == NULL)
	{
		return;
	}
	else if (m_skillLongRange != NULL && m_skillClose == NULL)
	{
		m_skillLongRange->removeAllChildren();
		_eventDispatcher->removeEventListener(m_skillMouseMove);
	}
	else
	{
		m_skillClose->removeAllChildren();
	}
	_eventDispatcher->removeEventListener(m_skillListener);
	m_skillLongRange = NULL;
	m_skillClose = NULL;
}