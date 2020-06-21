#include "HomeScene.h"
#include "SafeMapScene.h"
#include "AdventureMapScene.h"
#include "SettingScene.h"
#include "Scene/TollgateScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

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

	MenuItemImage* settingItem = MenuItemImage::create("menu/SettingNormal.png", "menu/SettingSelected.png", CC_CALLBACK_1(HomeMenuLayer::menuItemSettingCallback, this));
	settingItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 450, origin.y + visibleSize.height / 2 - 200));

	MenuItemImage* startItem = MenuItemImage::create("menu/StartNormal.png", "menu/StartSelected.png", CC_CALLBACK_1(HomeMenuLayer::menuItemStartCallback, this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 200, origin.y + visibleSize.height / 2 - 200));

	MenuItemImage* closeItem = MenuItemImage::create("menu/CloseNormal.png", "menu/CloseSelected.png", CC_CALLBACK_1(HomeMenuLayer::menuItemCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 200, origin.y + visibleSize.height / 2 - 200));

	Menu* menu = Menu::create(settingItem, startItem, closeItem, nullptr);

	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void HomeMenuLayer::onEnter()
{
	Layer::onEnter();
}

void HomeMenuLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() || GameData::getBgmNum() == ADVMAP)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/safeBgm.mp3", true);
		GameData::setBgmNum(SAFEMAP);
	}
}

void HomeMenuLayer::onExit()
{
	Layer::onExit();
}

void HomeMenuLayer::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void HomeMenuLayer::cleanup()
{
	Layer::cleanup();
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm/safeBgm.mp3");
}

void HomeMenuLayer::menuItemStartCallback(cocos2d::Ref* pSender)
{
	auto scene = SafeMapLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HomeMenuLayer::menuItemSettingCallback(cocos2d::Ref* pSender)
{
	auto scene = SettingLayer::createScene();
	Director::getInstance()->pushScene(scene);
}

void HomeMenuLayer::menuItemCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}