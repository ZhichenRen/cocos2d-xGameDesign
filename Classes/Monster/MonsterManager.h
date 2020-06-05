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
	void bindMap(AdventureMapLayer* map);
	void bindPlayer(Sprite* player);
	virtual bool init();
	virtual void update(float dt);
	void createMonsterPos();
	void resetAllMons();
	std::vector<Bullet*> getMonsterBullets();
	CC_SYNTHESIZE(AdventureMapLayer*, m_map, ManagerMap);
	CC_SYNTHESIZE(Sprite*, m_player);
private:
	std::vector<Monster*> m_monsterList;
	std::vector<Bullet*> m_monsterBullet;
	std::vector<Monster*> m_shortMonsterList;
	std::vector<Monster*> m_longMonsterList;
	const int pigNum = 3;
	const int slimeNum = 5;
	int m_checkPoint;
	std::map<Vec2, bool> m_monsPosMap;
	int m_dirs[4][2] = { {0,1}, {1,0}, {0,-1},{-1,0} };
	int m_deathMonsNum;
	//设置怪物数量，生成怪物，死了之后消失，生成一个金币
	//提供子弹的向量
	//Player* m_player;
};
#endif