#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Entity.h"
#include "Monster\Slime.h"
#include "Monster\Pig.h"
USING_NS_CC;
class MonsterManager : public Node {
public:
	MonsterManager();
	~MonsterManager();
	void createMonsters();
	CREATE_FUNC(MonsterManager);
	virtual bool init();
	virtual void update(float dt);
	void createMonsterPos();
private:
	Vector<Monster*> m_monsterList;
	//Player* m_player;
};
#endif