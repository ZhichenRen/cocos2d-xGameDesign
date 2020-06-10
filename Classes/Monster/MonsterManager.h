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
	void createMonsters();
	CREATE_FUNC(MonsterManager);
	void bindMap(AdventureMapLayer* map);
	void bindPlayer(Sprite* player);
	virtual bool init();
	virtual void update(float dt);
	void createMonsterPos();
	bool resetAllMons();
	std::vector<Bullet*> getMonsterBullets();
	bool isGameOver() { return m_fGameOver; }
	std::vector<Monster*> getMonster()const;
	CC_SYNTHESIZE(AdventureMapLayer*, m_map, ManagerMap);
private:
	std::vector<Monster*> m_monsterList;
	std::vector<Bullet*> m_monsterBullet;
	std::vector<Monster*> m_shortMonsterList;
	std::vector<Monster*> m_longMonsterList;
	Sprite* m_player;
	const int pigNum = 3;
	const int slimeNum = 5;
	int m_curCheckPoint;
	const int m_allCheckPoint = 3;
	std::map<Vec2, bool> m_monsPosMap;
	int m_dirs[4][2] = { {0,1}, {1,0}, {0,-1},{-1,0} };
	int m_deathMonsNum;
	bool m_fGameOver;
	//设置怪物数量，生成怪物，死了之后消失，生成一个金币	√
	//提供子弹的向量
	//Player* m_player;
	//野怪被嘲讽？
	//野怪翻转动画
};
#endif