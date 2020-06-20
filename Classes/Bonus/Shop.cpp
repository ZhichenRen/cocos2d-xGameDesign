#include "Bonus/Shop.h"
#include "Entity/Weapons/CandyGun.h"
#include "Entity/Weapons/RPG.h"
#include "Entity/Weapons/Shotgun.h"
#include "Entity/Weapons/GoldenSword.h"

Shop::Shop()
{
	m_interaction = 1;
	m_flowWord = FlowWord::create();
	this->addChild(m_flowWord);
	this->bindSprite(Sprite::create("cat.png"));
}

Shop::~Shop()
{
}

void Shop::bindSprite(Sprite* shopSprite)
{
	m_shop = shopSprite;
	this->addChild(m_shop);
}

void Shop::setInteractionNum(int num)
{
	m_interaction = num;
}

void Shop::setWeapon(int num)
{
	if (num == 1)
	{
		m_weapon = RPG::create();
	}
	else if (num == 2)
	{
		m_weapon = Shotgun::create();
	}
	else if (num == 3)
	{
		m_weapon = CandyGun::create();
	}
	else
	{
		m_weapon = GoldenSword::create();
	}
}

void Shop::showFlowWordFirstMeet()
{
	CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
	//pDictionary->removeAllObjects();
	//pDictionary->writeToFile("ChineseCharacters.plist");
	auto str = pDictionary->valueForKey("ShopFirstMeet")->getCString();
	m_flowWord->showShopWord(str);
}

void Shop::showFlowWordLackMoney()
{
	CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
	auto str = pDictionary->valueForKey("ShopLackMoney")->getCString();
	m_flowWord->showShopWord(str);
}

void Shop::showFlowWordEnoughMoney()
{
	CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
	auto str = pDictionary->valueForKey("ShopEnoughMoney")->getCString();
	m_flowWord->showShopWord(str);
}