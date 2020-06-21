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

	m_miniMap = TMXTiledMap::create("map/miniMap.tmx");
	//this->addChild(m_miniMap, 0, 300);

	this->scheduleUpdate();
	//loadMonsters();
	return true;
}

//像素坐标转换为瓦片坐标
cocos2d::Vec2 AdventureMapLayer::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / m_tileMap->getTileSize().width;
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - pos.y) / m_tileMap->getTileSize().height;

	return Vec2(x, y);
}


cocos2d::Point AdventureMapLayer::convertToMapSpace(const Point& point)
{
	return convertToNodeSpace(point);
}

std::map<Vec2, bool> AdventureMapLayer::getBarrierMap()
{
	return this->m_barrierMap;
}

bool AdventureMapLayer::isBarrier(Vec2 position)
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

bool AdventureMapLayer::isMonsterRoom(Vec2 roomCoord)
{
	return m_rooms[roomCoord] == ENEMY;
}

bool AdventureMapLayer::isBossRoom(Vec2 roomCoord)
{
	return m_rooms[roomCoord] == END && GameData::getLevel() == 2;
}

void AdventureMapLayer::update(float dt)
{
	for (auto it = m_blueList.begin(); it != m_blueList.end();)
	{
		if ((*it)->isUsed())
		{
			(*it)->removeFromParent();
			it = m_blueList.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = m_redList.begin(); it != m_redList.end();)
	{
		if ((*it)->isUsed())
		{
			(*it)->removeFromParent();
			it = m_redList.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = m_blueMedicineList.begin(); it != m_blueMedicineList.end();)
	{
		if ((*it)->isUsed())
		{
			(*it)->removeFromParent();
			it = m_blueMedicineList.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = m_coinList.begin(); it != m_coinList.end();)
	{
		if ((*it)->isUsed())
		{
			(*it)->removeFromParent();
			it = m_coinList.erase(it);
		}
		else
		{
			++it;
		}
	}
}