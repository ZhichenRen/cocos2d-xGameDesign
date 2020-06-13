#include "Scene/PlayerChoose.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;

bool PlayerChoose::init()
{
	if (!Layer::init())
	{
		return false;
	}
	loadUI();
	return true;
}

void PlayerChoose::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("PlayerInfo_1.ExportJson");
	this->addChild(UI, 0, 0);
	auto back_button = (Button*)Helper::seekWidgetByName(UI, "back_button");
	back_button->addTouchEventListener(this, toucheventselector(PlayerChoose::back));
	auto choose_button = (Button*)Helper::seekWidgetByName(UI, "choose_button");
	choose_button->addTouchEventListener(this, toucheventselector(PlayerChoose::setPlayer));
}

void PlayerChoose::setPlayer()
{
	//这里调用你的
}

void PlayerChoose::back()
{
	this->removeFromParentAndCleanup(true);
}