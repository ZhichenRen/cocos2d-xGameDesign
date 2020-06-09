#pragma once
#pragma once
#include "cocos2d.h"
#include "typeinfo"
#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"
#include "Entity/Item/Player/Ranger/Ranger.h"
#include "Controller/Move/PlayerController.h"
#include "Entity/Weapons/CandyGun.h"
#include "Scene/PauseScene.h"
#include "Scene/AdventureMapScene.h"
#include "Monster/MonsterManager.h"
#include "Bonus/Shop.h"
#include "Bonus/Chest.h"

#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
class TollgateScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	void addPlayer();
	void loadUI();
	void loadMonstersInNewRoom(int giantNum);
	void loadMap();
	void addLongRangeWeapon();
	void loadController();
	void loadMonsters();
	void loadListeners();
	void pauseEvent(Ref*, TouchEventType type);

	void updateMiniMap(TMXTiledMap* miniMap);
	void updateCoinNum();

	virtual void update(float dt);
	void menuOkCallback(Ref* pSender);


	CREATE_FUNC(TollgateScene);


private:
	LoadingBar* m_cdBar = NULL;
	LoadingBar* m_hpBar = NULL;
	LoadingBar* m_mpBar = NULL;
	Player* m_player;
	AdventureMapLayer* m_map;
	MonsterManager* m_monsterMgr;
};