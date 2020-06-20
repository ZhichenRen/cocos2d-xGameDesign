#include "Scene/AboutAuthor.h"
#pragma execution_character_set("utf-8")

bool AboutAuthor::init()
{
	if (!Layer::init())
	{
		return false;
	}
	loadUI();
	return true;
}

void AboutAuthor::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("AboutAuthor_1.ExportJson");
	this->addChild(UI, 0, 0);

	UI->setTouchEnabled(false);

	auto back_button = (Button*)Helper::seekWidgetByName(UI, "back_button");
	back_button->addTouchEventListener(this, toucheventselector(AboutAuthor::back));
	auto text = (Text*)Helper::seekWidgetByName(UI, "description");
	text->setText("四个南校区的倒霉蛋\n2.88元的捐赠可以让他们\n一人吃上一个南苑的肉包");

}

void AboutAuthor::back(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		this->removeFromParentAndCleanup(true);
		break;
	}
}