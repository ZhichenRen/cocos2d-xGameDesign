#pragma once
#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "GameData.h"
#include "Monster/Monster.h"
#include "Entity/Entity.h"
#include "Monster/Slime.h"
#include "Monster/Pig.h"
#include "Monster/ChiefOfTribe.h"
#include "Monster/Duck.h"
#include "Monster/Traveller.h"
#include "Monster/WoodWall.h"
#include "Monster/Boss.h"
#include "FlowWord/FlowWord.h"
#include "Bonus/chest.h"


USING_NS_CC;
class Player;
class MonsterManager : public Node {
public:
	//void createMonsters();
	void createMonsterPos();
	void createMonsters();
	
	CREATE_FUNC(MonsterManager);
	void bindMap(AdventureMapLayer* map);
	void bindPlayer(Entity* player);
	void bindMapForWeapon();
	void createRandomPos();
	void createWoodWalls(int woodWallsNum = 15);
	void createOneMoreMons();
	void createBoss();
	void reviveAllMonsters();
	bool resetAllMons();

	void killMonsters();
	void killWoodWall();

	virtual bool init();
	virtual void update(float dt);
	
	
	bool isGameOver()const;
	bool isPosOccupied(Vec2 pos);
	bool isRoomVisited(Vec2 room);
	bool isBossAlive() const;

	bool getInited()const;
	Vec2 getCurRoom()const;
	float getMonsterHpRate() const;
	std::vector<Bullet*> getMonsterBullets()const;
	std::vector<Monster*> getMonster()const;
	std::vector<Monster*> getWoodWall()const;
	std::map<Vec2, bool> getMonsPosMap()const { return m_monsPosMap; }

	void setPosMap(Vec2 pos, bool flag);
	void setCurRoom(Vec2 curRoom);
	void setBulkMonsterNum(int giantNum);
	void setInited();
	void setRoomVisited(Vec2 room);
	
private:

	void showPreRec();
	void hidePreRec();
	std::vector<int> createRandomNums(int numCnt, int sum);
	void bulkUpRandMons(int totalNum);
	
	std::vector<Monster*> m_monsterList;
	std::vector<Bullet*> m_monsterBullet;
	
	std::vector<Monster*> m_woodWallList;
	std::map<Vec2, bool> m_monsPosMap;
	std::map<Vec2, bool> m_visitedRoom;
	Boss* m_boss = NULL;
	FlowWord* m_flowWord = NULL;
	Entity* m_player = NULL;

	AdventureMapLayer* m_map = NULL;
	

	const int m_allCheckPoint = 4;
	int m_curCheckPoint;

	int m_dirs[4][2] = { {1,0}, {0,1}, {0,-1} ,{-1,0}};

	int m_deathMonsNum;
	bool m_fGameOver = false;
	Vec2 m_curRoom;
	int m_bulkMonsterNum;
	bool m_fIsInited = false;
};
#endif