#pragma once

#include "cocos2d.h"

class AdventureMapLayer : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* m_tileMap;
	cocos2d::TMXLayer* m_collidable;
	cocos2d::TMXLayer* m_ground;
	cocos2d::TMXLayer* m_wall;
	cocos2d::TMXLayer* m_road;
	cocos2d::Sprite* m_player;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyMap;
	std::map<cocos2d::Vec2, bool> m_barrierMap;

public:
	inline cocos2d::TMXTiledMap* getMap() { return m_tileMap; }
	inline cocos2d::TMXLayer* getCollidable() { return m_collidable; }
	inline  cocos2d::TMXLayer* getGround() { return m_ground; }
	inline cocos2d::TMXLayer* getWall() { return m_wall; }
	inline cocos2d::TMXLayer* getRoad() { return m_road; }
	inline cocos2d::Sprite* getPlayer() { return m_player; }
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void createRandomMap();

	virtual void buildRoom(cocos2d::Vec2 roomCoord);
	virtual void buildRoad(std::pair<cocos2d::Vec2, cocos2d::Vec2> roadPair);


	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

	cocos2d::Point convertToMapSpace(const cocos2d::Point& point);
	std::map<cocos2d::Vec2, bool> getBarrierMap();
	bool isBarrier(cocos2d::Vec2 position);

	// implement the "static create()" method manually
	CREATE_FUNC(AdventureMapLayer);
};

