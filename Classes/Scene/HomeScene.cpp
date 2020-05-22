#include "HomeScene.h"
#include "AdventureMapScene.h"
#include "SettingScene.h"


USING_NS_CC;

Scene* HomeMenuLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = HomeMenuLayer::create();

	scene->addChild(layer);

	return scene;
}

bool HomeMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	auto bg = Sprite::create("menu/Background.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	MenuItemImage* startItem = MenuItemImage::create("menu/StartNormal.png", "menu/StartSelected.png", CC_CALLBACK_1(HomeMenuLayer::menuItemStartCallback, this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 250, origin.y + visibleSize.height / 2));

	MenuItemImage* settingItem = MenuItemImage::create("menu/SettingNormal.png", "menu/SettingSelected.png", CC_CALLBACK_1(HomeMenuLayer::menuItemSettingCallback, this));
	settingItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 250, origin.y + visibleSize.height / 2));

	Menu* menu = Menu::create(startItem,settingItem,nullptr);

	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void HomeMenuLayer::menuItemStartCallback(cocos2d::Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HomeMenuLayer::menuItemSettingCallback(cocos2d::Ref* pSender)
{
	auto scene = SettingLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}
