#include "Scene//FinishScene.h"
#include "Scene/SafeMapScene.h"
#include "Scene/AboutAuthor.h"
#include "GameData.h"
#include "Scene/TollgateScene.h"

#pragma execution_character_set("utf-8")
#define RANGER 1
#define PRIEST 2
#define KNIGHT 3

extern restrorePlayer restore;

bool FinishScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

Scene* FinishScene::createScene(CCRenderTexture* background, int player)
{
	Scene* scene = Scene::create();
	FinishScene* layer = FinishScene::create();
	layer->setPlayer(player);
	layer->loadUI();
	scene->addChild(layer, 1);

	Size visible_size = Director::getInstance()->getVisibleSize();
	Sprite* background_picture = Sprite::createWithTexture(background->getSprite()->getTexture());
	background_picture->setPosition(visible_size.width / 2, visible_size.height / 2);
	background_picture->setFlippedY(true);
	scene->addChild(background_picture, 0);

	return scene;
}

void FinishScene::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("FinishScene_1.ExportJson");
	this->addChild(UI, 0, 0);

	UI->setTouchEnabled(false);

	auto home_button = (Button*)Helper::seekWidgetByName(UI, "home_button");
	home_button->addTouchEventListener(this, toucheventselector(FinishScene::backToHomeMenu));
	auto author_button = (Button*)Helper::seekWidgetByName(UI, "author_button");
	author_button->addTouchEventListener(this, toucheventselector(FinishScene::aboutAuthor));
	auto player_image = (ImageView*)Helper::seekWidgetByName(UI, "player_image");
	switch (m_player)
	{
	case RANGER:
		player_image->loadTexture("ranger_image.png");
		break;
	case PRIEST:
		player_image->loadTexture("priest_image.jpg");
		break;
	case KNIGHT:
		player_image->loadTexture("knight_image.png");
	}
}

void FinishScene::backToHomeMenu(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->popScene();
		GameData::setLastRoomCoord(Vec2(2, 2));
		GameData::setLevel(1);
		restore.num = 1;
		Director::getInstance()->replaceScene(HomeMenuLayer::createScene());
		break;
	}
}

void FinishScene::aboutAuthor(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		auto author_layer = AboutAuthor::create();
		this->addChild(author_layer, 3);
		break;
	}
}

void FinishScene::setPlayer(int player)
{
	m_player = player;
}