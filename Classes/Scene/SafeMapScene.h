#ifndef __SAFE_MAP_SCENE_H__
#define __SAFE_MAP_SCENE_H__

#include "cocos2d.h"

class SafeMapLayer :public cocos2d::Layer
{
	cocos2d::TMXTiledMap* m_tileMap;
	cocos2d::TMXLayer* m_collidable;
	cocos2d::Sprite* m_player;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyMap;
public:
	static cocos2d::Scene* createScene();

	virtual void update(float dt);

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void setPlayerPosition(cocos2d::Vec2 position, int dx, int dy);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	CREATE_FUNC(SafeMapLayer);
};


#endif // !__SAFE_MAP_SCENE_H__
