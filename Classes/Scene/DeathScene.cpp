#include "Scene/DeathScene.h"
#include "Scene/SafeMapScene.h"
#include "Entity/Item/Player/Player.h"
#include "Scene/AboutAuthor.h"
#include "GameData.h"

bool DeathScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	loadUI();
	return true;
}

Scene* DeathScene::createScene(CCRenderTexture* background, Player* player)
{
	Scene* scene = Scene::create();
	DeathScene* layer = DeathScene::create();
	layer->setPlayer(player);
	scene->addChild(layer, 1);

	Size visible_size = Director::getInstance()->getVisibleSize();
	Sprite* background_picture = Sprite::createWithTexture(background->getSprite()->getTexture());
	background_picture->setPosition(visible_size.width / 2, visible_size.height / 2);
	background_picture->setFlippedY(true);
	scene->addChild(background_picture, 0);

	return scene;
}

void DeathScene::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("DeathUI_1.ExportJson");
	this->addChild(UI, 0, 0);

	UI->setTouchEnabled(false);

	auto home_button = (Button*)Helper::seekWidgetByName(UI, "back_button");
	home_button->addTouchEventListener(this, toucheventselector(DeathScene::backToHomeMenu));
	auto respawn_button = (Button*)Helper::seekWidgetByName(UI, "respawn_button");
	respawn_button->addTouchEventListener(this, toucheventselector(DeathScene::respawn));
	auto author_button = (Button*)Helper::seekWidgetByName(UI, "author_button");
	author_button->addTouchEventListener(this, toucheventselector(DeathScene::aboutAuthor));
}

void DeathScene::backToHomeMenu(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->popScene();
		GameData::setCoinNum(0);
		GameData::setLastRoomCoord(Vec2(2, 2));
		GameData::setLevel(1);
		Director::getInstance()->replaceScene(SafeMapLayer::createScene());
		break;
	}
}

void DeathScene::respawn(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		//player do sth
		Director::getInstance()->popScene();
		break;
	}
}

void DeathScene::aboutAuthor(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		auto author_layer = AboutAuthor::create();
		this->addChild(author_layer, 3);
		break;
	}
}

void DeathScene::setPlayer(Player* player)
{
	m_player = player;
}