
#pragma once
#ifndef __SAFE_MAP_SCENE_H__

#define __SAFE_MAP_SCENE_H__

#include "cocos2d.h"
#include "Bonus/Shop.h"
#include "Scene/PlayerChoose.h"
#include "Scene/WeaponInfoScene.h"
#include "Scene/MonsterInfoScene.h"
#include "Scene/PauseScene.h"
#include "Scene/SettingScene.h"
#include "Scene/HomeScene.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "FlowWord/FlowWord.h"
using namespace cocos2d::ui;
using namespace cocostudio;

class SafeMapLayer :public cocos2d::Layer
{
	cocos2d::TMXTiledMap* m_tileMap;
	cocos2d::TMXLayer* m_collidable;
	cocos2d::Sprite* m_player;
	cocos2d::Sprite* m_weaponInfo;
	cocos2d::Sprite* m_monsterInfo;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyMap;

	cocos2d::EventListenerKeyboard* m_listener;

	FlowWord* m_flowWord;
public:
	static cocos2d::Scene* createScene();

	virtual void update(float dt);

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void setPlayer(int playerNum);

	void menuItemSettingCallback(cocos2d::Ref* pSender);
	void menuItemRangerCallback(cocos2d::Ref* pSender);
	void menuItemPriestCallback(cocos2d::Ref* pSender);
	void menuItemKnightCallback(cocos2d::Ref* pSender);

	void setPlayerPosition(cocos2d::Vec2 position, int dx, int dy);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);
	static int whichPlayer() { return m_choose_player; }

	CREATE_FUNC(SafeMapLayer);

	static int m_choose_player;
};


#endif // !__SAFE_MAP_SCENE_H__