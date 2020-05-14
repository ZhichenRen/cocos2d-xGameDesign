#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Entity/Entity.h"
USING_NS_CC;
const int MAX_MONSTER_NUM = 30;

class MonsterManager : public Entity {
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();
	virtual void update(float dt);
	void wander(Vec2 max);
	//void bindPlayer
private:
	void createMonsters();
	Vector<Monster*> m_monsterArr;
	//Player* m_player;
};
#endif