#pragma once
#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Entity.h"
#include "Monster\Slime.h"
#include "Monster\Pig.h"
USING_NS_CC;
class Player;
class MonsterManager : public Node {
public:
	void createMonsters();
	void createMonsterPos();

	CREATE_FUNC(MonsterManager);
	void bindMap(AdventureMapLayer* map);
	void bindPlayer(Entity* player);

	virtual bool init();
	virtual void update(float dt);


	bool resetAllMons();
	bool isGameOver() { return m_fGameOver; }

	std::vector<Bullet*> getMonsterBullets()const;
	std::vector<Monster*> getMonster()const;
	std::map<Vec2, bool> getMonsPosMap()const { return m_monsPosMap; }


private:
	std::vector<Monster*> m_monsterList;
	std::vector<Bullet*> m_monsterBullet;
	std::vector<Monster*> m_shortMonsterList;
	std::vector<Monster*> m_longMonsterList;
	std::map<Vec2, bool> m_monsPosMap;

	Entity* m_player = NULL;
	AdventureMapLayer* m_map;
	const int pigNum = 3;
	const int slimeNum = 5;
	const int m_allCheckPoint = 3;

	int m_curCheckPoint;
	int m_dirs[4][2] = { {0,1}, {1,0}, {0,-1},{-1,0} };
	int m_deathMonsNum;
	bool m_fGameOver = false;
	
	//提供子弹的向量 √
	//Player* m_player;
	//野怪被嘲讽？
	//野怪翻转动画√
	//设置怪物数量，生成怪物，死了之后消失，生成一个金币	√
};
#endif