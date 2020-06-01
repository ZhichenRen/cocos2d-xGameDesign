#ifndef __ADVENTURE_MAP_SCENE_H__
#define __ADVENTURE_MAP_SCENE_H__

#include "cocos2d.h"
class AdventureMapLayer : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* m_tileMap;
    cocos2d::TMXLayer* m_collidable;
    cocos2d::TMXLayer* m_ground;
    cocos2d::TMXLayer* m_wall;
    cocos2d::TMXLayer* m_road;
    cocos2d::Sprite* m_player;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyMap;
    
    std::map<cocos2d::Vec2, bool> m_barrierMap;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);

    virtual void createRandomMap();

    virtual void buildRoom(cocos2d::Vec2 roomCoord);
    virtual void buildRoad(std::pair<cocos2d::Vec2,cocos2d::Vec2> roadPair);
    //virtual void buildWall(std::pair<cocos2d::Vec2, cocos2d::Vec2> roadPair);


    void setPlayerPosition(cocos2d::Vec2 position,int dx,int dy);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);
	cocos2d::Point convertToMapSpace(const cocos2d::Point& point);
    std::map<cocos2d::Vec2, bool> getBarrierMap();
    // implement the "static create()" method manually
    CREATE_FUNC(AdventureMapLayer);
    bool AdventureMapLayer::isBarrier(cocos2d::Vec2 position);

};

#endif // __ADVENTURE_MAP_SCENE_H__
