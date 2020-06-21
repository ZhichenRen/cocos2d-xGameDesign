#pragma once
#include "cocos2d.h"
#include "typeinfo"
#include "Entity/Item/Player/Player.h"
#include "Entity/Item/Player/Ranger/Ranger.h"
#include "Controller/MyController.h"
#include "Entity/Item/Player/Player.h"

using namespace cocos2d;

class PlayerController :public MyController
{
public:
	virtual bool init() override;
	void onEnter();
	void onExit();
	CREATE_FUNC(PlayerController);
	virtual void update(float dt) override;
	void setPlayer(Player* player);
	virtual bool getIsChangeWeapon() const override { return m_isChangWeapon; }
	inline void setStandAnimate(Animate* animate) { m_standAnimate = animate; }
	inline void setIsRanger(bool isRanger) { m_isRanger = isRanger; }
	inline void setIsKnight(bool isKnight) { m_isKnight = isKnight; }
private:
	bool m_isChangWeapon = false;
	bool m_isRanger = false;
	bool m_isKnight = false;
	Player* m_player = NULL;
	EventListenerKeyboard* m_listener = NULL;
	void isEncounterBarriers(const int x, const int y);
	void registeControllerEvent();
	void animateOperate();
	void playerOperate()const;
	void rangerOpearte();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	Animate* m_walkAnimate = NULL;
	Animate* m_standAnimate = NULL;
	Sequence* m_rangerSkill = NULL;
};

