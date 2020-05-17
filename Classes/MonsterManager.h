#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Entity\Entity.h"
USING_NS_CC;
const int MAX_MONSTER_NUM = 30;
class MonsterPos;
class PosBase;
class PosLoadUtil;
class MonsterManager : public Node {
public:
	MonsterManager();
	~MonsterManager();
	/*static MonsterManager* createWithLevel(int iCurLevel);
	bool initWithLevel(int iCurLevel);*/
	void createMonsters();
	//int getNotShowMonsterCount();
	//Vector<Monster*> getMonsterList();
	/*MonsterPos* getMonsterStartPos();
	MonsterPos* getMonsterEndPos();*/
	CREATE_FUNC(MonsterManager);
	virtual bool init();
	virtual void update(float dt);
	//void wander(Vec2 max);
	//void bindPlayer
private:
	Vector<Monster*> m_monsterList;
	//Vector<Monster*> m_notShowMonsterList;
	
	float m_fShowTimeCount;
	void showMonster(float dt);
	//Player* m_player;
};
#endif