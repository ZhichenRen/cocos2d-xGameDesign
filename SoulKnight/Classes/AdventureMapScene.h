#ifndef __ADVENTURE_MAP_SCENE_H__
#define __ADVENTURE_MAP_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::Sprite* _player;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyMap;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void onEnter();
    virtual void onExit();

    virtual void update(float dt);

    //cocos2d::TMXTiledMap createRandomMap();

    void setPlayerPosition(cocos2d::Vec2 position,int dx,int dy);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __ADVENTURE_MAP_SCENE_H__
