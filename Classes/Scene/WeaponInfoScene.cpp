#include "Scene/WeaponInfoScene.h"

bool WeaponInfoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	loadUI();
	return true;
}

Scene* WeaponInfoScene::createScene(CCRenderTexture* background)
{
	Scene* scene = Scene::create();
	auto layer = WeaponInfoScene::create();
	scene->addChild(layer, 1);

	Size visible_size = Director::getInstance()->getVisibleSize();
	Sprite* background_picture = Sprite::createWithTexture(background->getSprite()->getTexture());
	background_picture->setPosition(visible_size.width / 2, visible_size.height / 2);
	background_picture->setFlippedY(true);
	scene->addChild(background_picture, 0);

	return scene;
}

void WeaponInfoScene::loadUI()
{
	m_ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("WeaponInfo_1.ExportJson");
	m_back_button = (Button*)Helper::seekWidgetByName(m_ui, "back_button");
	m_back_button->addTouchEventListener(this, toucheventselector(WeaponInfoScene::back));
	this->addChild(m_ui);
}

void WeaponInfoScene::back(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->popScene();
		break;
	}
}