#include "Bonus/Statue.h"

Statue::Statue()
{
	m_interaction = 1;
	m_flowWord = FlowWord::create();
	this->addChild(m_flowWord);
	this->bindSprite(Sprite::create("statue.png"));
}

Statue::~Statue()
{
}

void Statue::bindSprite(Sprite* statueSprite)
{
	m_statue = statueSprite;
	this->addChild(m_statue);
}

void Statue::setInteractionNum(int num)
{
	m_interaction = num;
}

void Statue::showFlowWordFirstMeet()
{
	CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
	auto str = pDictionary->valueForKey("StatueFirstMeet")->getCString();
	m_flowWord->showShopWord(str);
}

void Statue::showFlowWordLackMoney()
{
	CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
	auto str = pDictionary->valueForKey("StatueLackMoney")->getCString();
	m_flowWord->showShopWord(str);
}

void Statue::showFlowWordEnoughMoney()
{
	CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
	auto str = pDictionary->valueForKey("StatueEnoughMoney")->getCString();
	m_flowWord->showShopWord(str);
}