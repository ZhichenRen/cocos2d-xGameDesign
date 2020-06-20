#include "FlowWord/FlowWord.h"

bool FlowWord::init()
{
	m_message = Label::create("", "Arial", 24);
	m_message->setColor(Color3B(255, 255, 255));
	m_message->setVisible(false);

	this->addChild(m_message);
	return true;
}

void FlowWord::showWord(const char* text, Point pos)
{
	m_message->setPosition(Point(pos.x + 30, pos.y + 30));
	m_message->setString(text);

	m_message->setVisible(true);
	auto delay = DelayTime::create(0.5f);

	auto callBack = CallFunc::create
	(
		[&]()
	{
		m_message->setVisible(false);
		m_message->removeFromParentAndCleanup(true);
	}
	);
	auto actions = Sequence::create(delay, callBack, NULL);

	this->runAction(actions);
}

void FlowWord::showShopWord(const char* text)
{
	m_message->setString(text);
	m_message->setColor(Color3B(255, 255, 255));
	m_message->setPosition(getPosition() + Vec2(0, 50));

	m_message->setVisible(true);
	auto scaleUp = ScaleBy::create(0.2f, 1.2);
	auto scaleDown = ScaleTo::create(3.0f, 1.0 / 1.2);

	auto callBack = CallFunc::create
	(
		[&]()
	{
		m_message->setVisible(false);
		//m_message->removeFromParentAndCleanup(true);
	}
	);
	auto actions = Sequence::create(scaleUp, scaleDown, callBack, NULL);

	this->runAction(actions);
}


void FlowWord::showMonsDmg(const char* text, float ySize, float time)
{
	m_message->setString(text);
	m_message->setPosition(getPosition() + ccp(0, 5 + ySize));
	m_message->setColor(Color3B(220, 20, 60));
	m_message->setVisible(true);
	m_message->stopAllActions();
	auto scaleUp = ScaleBy::create(time, 1.2);
	auto scaleDown = ScaleTo::create(time, 1);

	auto callBack = CallFunc::create
	(
		[&]()
	{
		m_message->setVisible(false);
		//m_message->removeFromParentAndCleanup(true);
	}
	);
	auto actions = Sequence::create(scaleUp, scaleDown, callBack, NULL);

	this->runAction(actions);
}

void FlowWord::showCritDmg(const char* text, float ySize, float time)
{
	m_message->setString(text);
	m_message->setColor(Color3B(255, 0, 0));
	m_message->setPosition(getPosition() + ccp(0, 5 + ySize));
	m_message->setVisible(true);
	//auto rewindToStdSize = ScaleTo::create(0.2f, 1);
	auto scaleUp = ScaleBy::create(time, 2.0);
	auto scaleDown = ScaleTo::create(time + 0.1, 1);

	auto callBack = CallFunc::create
	(
		[&]()
	{
		m_message->setVisible(false);
		//m_message->removeFromParentAndCleanup(true);
	}
	);
	auto actions = Sequence::create(scaleUp, scaleDown, callBack, NULL);

	this->runAction(actions);
}

void FlowWord::showMonsTaunted()
{
	m_message->setString("!!");
	m_message->setColor(Color3B(255, 255, 255));
	m_message->setPosition(getPosition() + ccp(0, 40));
	m_message->setVisible(true);
	auto scaleUp = ScaleBy::create(0.2f, 2.0);
	auto scaleDown = ScaleTo::create(0.6f, 1);
	auto callBack = CallFunc::create
	(
		[&]()
	{
		m_message->setVisible(false);
		//m_message->removeFromParentAndCleanup(true);
	}
	);
	auto actions = Sequence::create(scaleUp, scaleDown, callBack, NULL);
	this->runAction(actions);
}