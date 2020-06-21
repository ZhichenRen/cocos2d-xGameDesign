#pragma once
#ifndef __Monster_H__
#define __Monster_H__
#define BLUERATE 0.75f
#define REDRATE 0.0025f
#define BLUEMEDICINERATE 0.005f
#include "Entity/Entity.h"
#include "cocos2d.h"
#include "Entity\Coin\Coin.h"
#include "Entity\Weapons\MonsterGun.h"
#include "Entity/Blue/Blue.h"
#include "Entity/Red/Red.h"
#include "FlowWord/FlowWord.h"
#include "Entity/BlueMedicine/BlueMedicine.h"


USING_NS_CC;
class MonsterManager;
class Monster :public Entity {
public:
	Monster();
	bool isCollideWith(Entity* entity);
	~Monster();
	virtual bool init();
	CREATE_FUNC(Monster);
public:
	void show();
	void hide();
	void hit(int damage);
	void bindMap(AdventureMapLayer* map);
	void bindMonsMgr(MonsterManager* monsMgr);
	virtual void hit(int damage, float flyingDegree, bool isCriticalStrike);
	virtual void die();
	void wander();
	//void showWords();
	//void dieWithNothing();
	void setMonsTaunted();
	FlowWord* getFlowWord() const;
	bool isAlive()const;
	bool isTaunted()const;
	bool setTaunted(bool flag);
	bool mySetPosition(Vec2 target);
	void bulkUp();
	virtual void resetPropoties();

	CC_SYNTHESIZE(float, m_fSpeed, MonsterSpeed);
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(std::string, m_resTrack, ResTrack);

	CC_SYNTHESIZE(Weapon*, m_weapon, MonsterWeapon);
protected:
	AdventureMapLayer* m_map;
	MonsterManager* m_monsMgr;
	bool m_fIsFacingRight = false;
	bool m_fIsTaunted = false;
	bool m_isAlive = false;
	bool m_isBulkUp = false;
	FlowWord* m_damageMsg;
	Sprite* m_preRec;

};
#endif // !__Monster_H__