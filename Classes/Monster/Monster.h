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
	bool isAlive();
	void mySetPosition(Vec2 target);
	void hit(int damage);
	void bindMap(AdventureMapLayer* map) { m_map = map; }
	void bindMonsMgr(MonsterManager* monsMgr) { m_monsMgr = monsMgr; }
	void hit(int damage, float flyingDegree);
	void die();
	virtual void resetPropoties() { m_isAlive = true; }
	
	CC_SYNTHESIZE(float, m_fSpeed, MonsterSpeed);
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(std::string, m_resTrack, ResTrack);
	CC_SYNTHESIZE(bool, m_isAlive);
	CC_SYNTHESIZE(Weapon*, m_weapon, MonsterWeapon);
protected:
	AdventureMapLayer* m_map;
	MonsterManager* m_monsMgr;
	bool m_fIsFacingRight;
};
#endif // !__Monster_H__