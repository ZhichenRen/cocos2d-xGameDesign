#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Entity.h"
#include "Monster\Slime.h"
USING_NS_CC;
const int MAX_MONSTER_NUM = 30;
class MonsterManager : public Node {
public:
	MonsterManager();
	~MonsterManager();
	void createMonsters();
	CREATE_FUNC(MonsterManager);
	virtual bool init();
	virtual void update(float dt);
	void createMonsterPos();
	//std::vector<Vec2> m_monsterPos;
	//void wander(Vec2 max);
	//void bindPlayer
private:
	Vector<Monster*> m_monsterList;
	float m_fShowTimeCount;
	void showMonster(float dt);
	//Player* m_player;
};
#endif