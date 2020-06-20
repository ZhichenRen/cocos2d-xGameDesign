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
#include "Bonus/Statue.h"

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
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	void addPlayer();
	void loadUI();
	void loadMonstersInNewRoom();
	void loadMap();
	void addWeapon();
	void loadController();
	void loadMonsters();
	void loadBoss();
	void loadListeners();
	void loadEditBox();
	void pauseEvent(Ref*, TouchEventType type);
	void switchWeapon(Ref*, TouchEventType type);

	void updateMiniMap(TMXTiledMap* miniMap);
	void updateCoinNum();
	void compare(float dt);
	virtual void update(float dt);
	void menuOkCallback(Ref* pSender);


	CREATE_FUNC(TollgateScene);


private:
	cocos2d::ui::EditBox* m_editBox;
	FlowWord* m_flowWord;
	LoadingBar* m_cdBar = NULL;
	LoadingBar* m_hpBar = NULL;
	LoadingBar* m_mpBar = NULL;
	LoadingBar* m_armorBar = NULL;
	LoadingBar* m_boss_hp = NULL;
	LoadingBar* m_boss_hp_bg = NULL;
	Text* m_boss_name = NULL;
	Text* m_hp = NULL;
	Text* m_armor = NULL;
	Text* m_mp = NULL;
	Text* m_coin = NULL;
	Text* m_mp_cost = NULL;
	ImageView* m_weapon_image = NULL;
	Button* m_weapon_button = NULL;
	Player* m_player = NULL;
	AdventureMapLayer* m_map;
	MonsterManager* m_monsterMgr;
	EventListenerKeyboard* m_keyboard_listener = NULL;
	Widget* UI = NULL;
};

class restrorePlayer
{
public:
	Player* m_player;
	std::array<std::string, 10> weapons;
	std::array<bool, 10> m_isUpgrate;
	std::array <LongRange*, 5> m_longRanges;
	int m_totalHp;
	int m_nowHp;
	int m_totalArmor;
	int m_nowArmor;
	int m_totalMp;
	int m_nowMp;

	int m_numWeapon;
	int m_numHasWeapon;
	int m_numTotalWeapon;
	int m_longRange;
	int num = 1;
};