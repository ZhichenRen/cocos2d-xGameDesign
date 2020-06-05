#pragma once
#ifndef __Monster_H__
#define __Monster_H__
#define BLUERATE 0.3

#include "Entity/Entity.h"
#include "cocos2d.h"
#include "Entity\Coin\Coin.h"
#include "Entity\Weapons\MonsterGun.h"
#include "Entity/Blue/Blue.h"
USING_NS_CC;
class MonsterManager;
class Monster :public Entity {
public:
	Monster();
	~Monster();
	virtual bool init();
	CREATE_FUNC(Monster);
public:
	void show();
	void hide();
	void hit(int damage);
	void bindMap(AdventureMapLayer* map);
	void bindMonsMgr(MonsterManager* monsMgr);
	void hit(int damage, float flyingDegree);
	void die();
	void wander();

	bool isAlive();
	bool isTaunted();
	bool setTaunted(bool flag);
	bool mySetPosition(Vec2 target);

	virtual void resetPropoties();
	
	CC_SYNTHESIZE(float, m_fSpeed, MonsterSpeed);
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(std::string, m_resTrack, ResTrack);
	CC_SYNTHESIZE(bool, m_isAlive);
	CC_SYNTHESIZE(Weapon*, m_weapon, MonsterWeapon);
protected:
	AdventureMapLayer* m_map;
	MonsterManager* m_monsMgr;
	bool m_fIsFacingRight = false;
	bool m_fIsTaunted = false;
};
#endif // !__Monster_H__