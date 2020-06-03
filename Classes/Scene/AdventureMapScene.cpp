#include "Scene\AdventureMapScene.h"
#include "SimpleAudioEngine.h"
#include "Entity\Coin\Coin.h"
//#include "Entity\Weapons\RPG.h"
//#include "Entity\Weapons\Shotgun.h"
#include "Entity\Weapons\CandyGun.h"
#include "Monster/MonsterManager.h"
USING_NS_CC;

Scene* AdventureMapLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = AdventureMapLayer::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool AdventureMapLayer::init()
{
	//1. super init first
	if (!Layer::init())
	{
		return false;
	}

	createRandomMap();
	this->addChild(m_tileMap, 0, 100);//游戏地图 tag为100

	//loadMonsters();
	return true;
}


//像素坐标转换为瓦片坐标
cocos2d::Vec2 AdventureMapLayer::tileCoordFromPosition(cocos2d::Vec2 pos)
{
	int x = pos.x / m_tileMap->getTileSize().width;
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - pos.y) / m_tileMap->getTileSize().height;

	return Vec2(x, y);
}


cocos2d::Point AdventureMapLayer::convertToMapSpace(const cocos2d::Point& point)
{
	return convertToNodeSpace(point);
}

std::map<Vec2, bool> AdventureMapLayer::getBarrierMap()
{
	return this->m_barrierMap;
}

bool AdventureMapLayer::isBarrier(cocos2d::Vec2 position)
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);//像素坐标转换为瓦片坐标

	int tileGid = m_collidable->getTileGIDAt(tileCoord);//获得瓦片的GID

	if (tileGid != 0)//瓦片是否存在（不存在时tileGid==0）
	{
		auto prop = m_tileMap->getPropertiesForGID(tileGid);
		auto valueMap = prop.asValueMap();
		return valueMap["Collidable"].asBool();
	}
	return false;
}