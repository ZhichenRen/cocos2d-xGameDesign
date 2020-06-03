#include "Scene/TollgateScene.h"

Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	Director::getInstance()->setProjection(Director::Projection::_2D);
	return scene;
}

void TollgateScene::loadMap()
{
	m_map = AdventureMapLayer::create();
	this->addChild(m_map, 0, 100);//游戏地图 tag为100

}

void TollgateScene::addPlayer()
{
	TMXObjectGroup* group = m_map->getMap()->getObjectGroup("objects");//获取对象层
	ValueMap spawnPoint = group->getObject("hero");//根据hero对象的位置放置精灵
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	m_player = Ranger::create();
	m_player->setPosition(Vec2(x, y));

	m_player->setTiledMap(m_map);
	m_player->setCdBar(m_cdBar);
	m_map->addChild(m_player, 2, 200);
}

void TollgateScene::addLongRangeWeapon()
{
	m_player->setLongRange(CandyGun::create());
}

void TollgateScene::loadController()
{
	auto animate = m_player->stand();
	auto* playerController = PlayerController::create();
	playerController->setiXSpeed(0);
	playerController->setiYSpeed(0);
	this->addChild(playerController);
	m_player->setController(playerController);
	playerController->setPlayer(m_player);
	playerController->setIsRanger(typeid(*m_player) == typeid(Ranger));//以后与memberSelect结合
	playerController->setStandAnimate(animate);

}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;
	loadMap();
	loadUI();
	addPlayer();
	addLongRangeWeapon();
	loadController();


	return true;
}

void TollgateScene::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("INGAME_1.ExportJson");
	this->addChild(UI, 0, 0);
	m_cdBar = (LoadingBar*)Helper::seekWidgetByName(UI, "ability_loading_bar");

	/*auto pause_button = (Button*)Helper::seekWidgetByName(UI, "pause_button");
	pause_button->addTouchEventListener(this, toucheventselector(HelloWorld::pauseEvent));*/
}

