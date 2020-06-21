#include "Entity/Item/Player/Player.h"
#include "Scene/TollgateScene.h"
#include "FlowWord/FlowWord.h"
#include "Entity/Weapons/CloseWeapon.h"
#include "Entity\Weapons\Shotgun.h"
#include "Entity\Weapons\RPG.h"
#include "Entity\Weapons\GoldenSword.h"
#include "Entity\Weapons\CandyGun.h"
#include "Entity/Weapons/TrackWeapon.h"
#include "Entity/Weapons/Pistol.h"
#include "Entity/Weapons/StoneSword.h"

bool Player::init()
{
	if (!Item::init())
	{
		return false;
	}
	m_is_attacking = false;
	m_is_close_weapon_now = false;
	this->scheduleUpdate();
	return true;
}

bool Player::isCollideWith(Entity* entity)
{
	return getBoundingBox().intersectsRect(entity->getBoundingBox());
}

void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)
		return;
	Layer* parent = (Layer*)getParent();
	Size mapTiledNum = m_map->getMap()->getMapSize();
	Size tiledSize = m_map->getMap()->getTileSize();

	Size mapSize = Size(mapTiledNum.width * tiledSize.height, mapTiledNum.height * tiledSize.height);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point spritePos = getPosition();

	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);
	Point destPos = Point(x, y);
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centerPos - destPos;
	parent->setPosition(viewPos);
}


void Player::setTagPosition(const int x, const int y)
{

	Item::setTagPosition(x, y);
	setViewPointByPlayer();
}

void Player::setTiledMap(AdventureMapLayer* map)
{
	this->m_map = map;
}

void Player::setiNowCD(int cd)
{
	if (cd > m_iTotalCD)
		m_iNowCD = m_iTotalCD;
	else if (cd < 0)
		m_iNowCD = 0;
	else
		m_iNowCD = cd;
}

void Player::setiTotalCD(int cd)
{
	if (cd < 0)
		m_iTotalCD = 0;
	else
		m_iTotalCD = cd;
}

void Player::setiNowMp(int mp)
{
	if (mp > m_iTotalMp)
		m_iNowMp = m_iTotalMp;
	else if (mp < 0)
		m_iNowMp = 0;
	else
		m_iNowMp = mp;
}

void Player::setiTotalMp(int mp)
{
	if (mp < 0)
		m_iTotalMp = 0;
	else
		m_iTotalMp = mp;
}

Point Player::tileCoordForPosition(Point pos)
{
	int x = pos.x / ((m_map->getMap())->getTileSize().width);
	int y = ((m_map->getMap()->getMapSize().height * m_map->getMap()->getTileSize().height) - pos.y)
		/ ((m_map->getMap())->getTileSize().height);

	return Point(x, y);
}

void Player::setiNowSkillDuration(int duration)
{
	if (duration > m_iTotalSkillDuration)
		m_iNowSkillDuration = m_iTotalSkillDuration;
	else if (duration < 0)
		m_iNowSkillDuration = 0;
	else
		m_iNowSkillDuration = duration;
}

void Player::setiTotalSkillDuration(int duration)
{
	if (duration < 0)
		m_iTotalSkillDuration = 0;
	else
		m_iTotalSkillDuration = duration;
}

int Player::isPositiveOrNegative(int num)
{
	if (num > 0)
		return 1;
	else if (num < 0)
		return -1;
	else
		return 0;
}

void Player::changeWeapon()
{
	m_numWeapon--;
	if (m_numWeapon == 0)
		m_numWeapon = m_numHasWeapon;
	int numLongRange = 0, numCloseWeapon = 0;
	determineWhichWeapon();
}


void Player::chooseAbondonWeapon()
{
	m_longRangeAbondon = NULL;
	m_closeAbondon = NULL;
	if (m_weapons[m_numWeapon - 1] == "CandyGun!")
	{
		m_closeAbondon = NULL;
		m_longRangeAbondon = CandyGun::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRangeAbondon->upgrade();
	}
	else if (m_weapons[m_numWeapon - 1] == "GoldenSword!")
	{
		m_longRangeAbondon = NULL;
		m_closeAbondon = GoldenSword::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_closeAbondon->upgrade();
	}
	else if (m_weapons[m_numWeapon - 1] == "Fist_of_Heaven")
	{
		m_closeAbondon = NULL;
		m_longRangeAbondon = RPG::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRangeAbondon->upgrade();
	}
	else if (m_weapons[m_numWeapon - 1] == "Rifle&Shotgun")
	{
		m_closeAbondon = NULL;
		m_longRangeAbondon = Shotgun::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRangeAbondon->upgrade();
	}
	else if (m_weapons[m_numWeapon - 1] == "Pistol")
	{
		m_closeAbondon = NULL;
		m_longRangeAbondon = Pistol::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRangeAbondon->upgrade();
	}
	else if (m_weapons[m_numWeapon - 1] == "StoneSword")
	{
		m_longRangeAbondon = NULL;
		m_closeAbondon = StoneSword::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_closeAbondon->upgrade();
	}
}

void Player::abandonWeapon()
{
	chooseAbondonWeapon();
	if (m_closeAbondon == NULL && m_longRangeAbondon != NULL)
	{
		if (m_rightSide)
			m_longRangeAbondon->setPosition(getTagPosition());
		else
			m_longRangeAbondon->setPosition(getTagPosition());
		m_map->addChild(m_longRangeAbondon,3,200);
		m_map->addLongRange(m_longRangeAbondon);
	}
	else if (m_longRangeAbondon == NULL && m_closeAbondon != NULL)
	{
		if (m_rightSide)
			m_closeAbondon->setPosition(getTagPosition());
		else
			m_closeAbondon->setPosition(getTagPosition());
		m_closeAbondon->bindMap(m_map);
		m_map->addChild(m_closeAbondon,3,200);
		m_map->addCloseWeapon(m_closeAbondon);
	}
}

void Player::setWeapon(std::string& str,const bool isUpgrate)
{
	for (int i = 0; i < m_numHasWeapon; i++)
	{
		if (str == m_weapons[i] && m_isUpgrate[i] == false)
		{
			m_isUpgrate[i] = true;
			m_numWeapon = i + 1;
			auto* flowWord = FlowWord::create();
			this->addChild(flowWord);
			std::string msg = "Upgrade!";
			flowWord->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
			return;
		}
	}
	if (m_numHasWeapon < m_numTotalWeapon)
	{
		m_numHasWeapon++;
		m_numWeapon = m_numHasWeapon;
		m_weapons[m_numWeapon - 1] = str;
		m_isUpgrate[m_numWeapon - 1] = isUpgrate;
	}
	else
	{
		abandonWeapon();
		m_weapons[m_numWeapon - 1] = str;
		m_isUpgrate[m_numWeapon - 1] = isUpgrate;
	}
}

void Player::resetWeapon()
{
	if (m_longRange == NULL && m_close == NULL)
	{
		return;
	}
	else if (m_longRange != NULL && m_close == NULL)
	{
		m_longRange->removeAllChildren();
		_eventDispatcher->removeEventListener(m_mouseMove);
	}
	else
	{
		m_close->removeAllChildren();
	}
	_eventDispatcher->removeEventListener(m_listener);
}

void Player::chooseWeapon()
{
	if (m_weapons[m_numWeapon - 1] == "CandyGun!")
	{
		m_close = NULL;
		m_longRange = CandyGun::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRange->upgrade();
		m_is_close_weapon_now = false;
		m_weaponFileName = "CandyGun!.png";
		m_weaponPowerCost = m_longRange->getPowerCost();
		loadLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "GoldenSword!")
	{
		m_longRange = NULL;
		m_close = GoldenSword::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_close->upgrade();
		m_is_close_weapon_now = true;
		m_weaponFileName = "GoldenSword!.png";
		m_weaponPowerCost = m_close->getPowerCost();
		loadCloseWeaponListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "Fist_of_Heaven")
	{
		m_close = NULL;
		m_longRange =RPG::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRange->upgrade();
		m_is_close_weapon_now = false;
		m_weaponFileName = "Fist_of_Heaven.png";
		m_weaponPowerCost = m_longRange->getPowerCost();
		loadLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "Rifle&Shotgun")
	{
		m_close = NULL;
		m_longRange = Shotgun::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRange->upgrade();
		m_is_close_weapon_now = false;
		m_weaponFileName = "Rifle&Shotgun.png";
		m_weaponPowerCost = m_longRange->getPowerCost();
		loadLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "Pistol")
	{
		m_close = NULL;
		m_longRange = Pistol::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_longRange->upgrade();
		m_is_close_weapon_now = false;
		m_weaponFileName = "pistol.png";
		m_weaponPowerCost = m_longRange->getPowerCost();
		loadLongRangeListener();
	}
	else if (m_weapons[m_numWeapon - 1] == "StoneSword")
	{
		m_longRange = NULL;
		m_close = StoneSword::create();
		if (m_isUpgrate[m_numWeapon - 1] == true)
			m_close->upgrade();
		m_is_close_weapon_now = true;
		m_weaponFileName = "StoneSword.png";
		m_weaponPowerCost = m_close->getPowerCost();
		loadCloseWeaponListener();
	}
}

void Player::determineWhichWeapon()
{
	resetWeapon();
	chooseWeapon();
	if (m_longRange != NULL && m_close == NULL)
	{
		if(m_leftSide)
			m_longRange->setPosition(-15, -5);
		else
		    m_longRange->setPosition(15, -5);
		m_longRange->bindMap(m_map);
		this->addChild(m_longRange);
	    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_mouseMove, this);
	}
	else
	{
		if (m_rightSide)
			m_close->setPosition(15, -9);
		else
			m_close->setPosition(-15, -9);
		m_close->bindMap(m_map);
		this->addChild(m_close);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	}
	
}

int Player::findWhichLongRange()const
{
	if (m_numLongRange % 5 == 0)
		return 4;
	else
	{
		return m_numLongRange % 5 - 1;
	}
}

void Player::loadLongRangeListener()
{
	m_numLongRange++;
	LongRange* longRange = m_longRange;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = [longRange,this](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());

		if (m_iNowMp >= longRange->getPowerCost())
		{
			m_is_attacking = true;

			//call back to change attack status
			auto attack_delay = DelayTime::create(m_longRange->getAttackSpeed());
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
	m_listener = listener;
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
	m_mouseMove = mouse_move;
}

void Player::loadCloseWeaponListener()
{
	CloseWeapon* closeWeapon = m_close;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = [closeWeapon, this](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (m_iNowMp >= m_close->getPowerCost())
		{
			m_is_attacking = true;

			//call back to change attack status
			auto attack_delay = DelayTime::create(m_close->getAttackSpeed());
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
	m_listener = listener;

}

void Player::setRightToward()
{
	if (this->getRightSide() == true)
	{
		this->setLeftSide(true);
		this->setRightSide(false);
		m_sprite->setFlipX(true);
		if (m_isKightSkill == false)
		{
			if (m_longRange == NULL && m_close != NULL)
			{
				m_close->setPosition(m_close->getPosition().x * (-1), -9);
			}
			else if (m_longRange != NULL && m_close == NULL)
			{
				m_longRange->setPosition(m_longRange->getPosition().x * (-1), -5);
			}
		}
	}
}

void Player::setLeftToward()
{
	if (this->getLeftSide() == true)
	{
		this->setLeftSide(false);
		this->setRightSide(true);
		m_sprite->setFlipX(false);
		if (m_isKightSkill == false)
		{
			if (m_longRange == NULL && m_close != NULL)
			{
				m_close->setPosition(m_close->getPosition().x*(-1), -9);
			}
			else if (m_longRange != NULL && m_close == NULL)
			{
				m_longRange->setPosition(m_longRange->getPosition().x * (-1), -5);
			}
		}
	}
}

void Player::resetWeaponPosition(bool status)
{
	if (!m_is_attacking)
	{
		m_longRange->flipped(status);
		m_longRange->resetPosition();
	}
}

std::vector<Bullet*> Player::getBullet()
{
	std::vector<Bullet*> bullets;
	if (m_numLongRange!=0)
	{
		int n = std::min(m_numLongRange, 5);
		for (int i = 0; i < n; i++)
		{
			auto longRange = m_longRanges[i];
			if (longRange == NULL)
				continue;
			for (auto bullet : longRange->getBullet())
			{
				bullets.push_back(bullet);
			}
		}
	}
	return bullets;
}

void Player::hit(int damage)
{
	if (damage < getiNowArmor())
		setiNowArmor(getiNowArmor() - damage);
	else
	{
		setiNowHp(getiNowHp() - (damage - getiNowArmor()));
		setiNowArmor(0);
	}
}

void Player::getBulletFromWeapon()
{

}

void Player::setiNowArmor(int armor)
{
	if (armor > m_iTotalArmor)
		m_iNowArmor = m_iTotalArmor;
	else if (armor < 0)
		m_iNowArmor = 0;
	else
		m_iNowArmor = armor;
}

void Player::setiTotalArmor(int armor)
{
	if (armor < 0)
		m_iTotalArmor = 0;
	else
		m_iTotalArmor = armor;
}

void Player::setArmorCd()
{
	if (m_iArmorCd == 0 && getiNowArmor() == getiTotalArmor())
	{
		return;
	}
	else if (m_iArmorCd == 100)
	{
		setiNowArmor(getiNowArmor() + 1);
		m_iArmorCd = 0;
	}
	else
		m_iArmorCd++;
}

void Player::mpDepletion(int mpDe)
{
	setiNowMp(getiNowMp() - mpDe);
}

bool Player::isAttackingWithCloseWeapon()const
{
	return m_is_close_weapon_now && m_is_attacking;
}

CloseWeapon* Player::getCloseWeapon()const
{
	return m_close;
}

LongRange* Player::getLongrange()const
{
	return m_longRange;
}

bool Player::isClose()const
{
	return m_is_close_weapon_now;
}

void Player::getBuff(int i)
{
	if (i == 0)
	{
		auto m_addBloodMsg = FlowWord::create();
		this->addChild(m_addBloodMsg);
		std::string msg = "Hp up!";
		m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
		setiTotalHp(getiTotalHp() + 2);
		setiNowHp(getiNowHp() + 2);
	}
	else if (i == 1)
	{
		auto m_addBloodMsg = FlowWord::create();
		this->addChild(m_addBloodMsg);
		std::string msg = "Mp up!";
		m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
		setiTotalMp(getiTotalMp() + 50);
		setiNowMp(getiNowMp() + 50);
	}
	else if (i == 2)
	{
		auto m_addBloodMsg = FlowWord::create();
		this->addChild(m_addBloodMsg);
		std::string msg = "Faster cooling!";
		m_addBloodMsg->showCritDmg(msg.c_str(), this->getContentSize().height / 2, 1.0);
		setiTotalCD(getiTotalCD() / 2);
		setiNowCD(getiNowCD() / 2);
	}
}

void Player::setInvincible(float duration_time)
{
	if (m_is_invincible)
	{
		return;
	}
	m_is_invincible = true;
	m_shield->setVisible(true);
	auto duration = DelayTime::create(duration_time);
	auto callback = CallFunc::create(
		[this]()
	{
		this->m_is_invincible = false;
		this->m_shield->setVisible(false);
	}
	);
	auto action = Sequence::create(duration, callback, NULL);
	this->runAction(action);
}

bool Player::isInvincible()const
{
	return m_is_invincible;
}

void Player::setDamageBonus(int bonus_time, float duration_time)
{
	m_damage_bonus = bonus_time;
	auto duration = DelayTime::create(duration_time);
	auto callback = CallFunc::create(
		[this]()
	{
		this->m_damage_bonus = 1;
	}
	);
	auto action = Sequence::create(duration, callback, NULL);
	this->runAction(action);
}

int Player::getDamageBonus()const
{
	return m_damage_bonus;
}