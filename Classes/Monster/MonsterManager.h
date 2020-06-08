#pragma once
#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Entity.h"
#include "Monster\Slime.h"
#include "Monster\Pig.h"
#include "Monster\ChiefOfTribe.h"
#include "Monster\Duck.h"
USING_NS_CC;
class Player;
class MonsterManager : public Node {
public:
	void createMonsters();
	void createMonsterPos();

	CREATE_FUNC(MonsterManager);
	void bindMap(AdventureMapLayer* map);
	void bindPlayer(Entity* player);
	void createRandomPos();
	
	void reviveAllMonsters();
	virtual bool init();
	virtual void update(float dt);


	bool resetAllMons();
	bool isGameOver();

	std::vector<Bullet*> getMonsterBullets()const;
	std::vector<Monster*> getMonster()const;
	std::map<Vec2, bool> getMonsPosMap()const { return m_monsPosMap; }
	void setPosMap(Vec2 pos, bool flag);
	

	void setCurRoom(Vec2 curRoom);
	Vec2 getCurRoom();
	bool isPosOccupied(Vec2 pos) ;
	void markRoomVisited(Vec2 room);
	bool isRoomVisited(Vec2 room);
private:

	void showPreRec();
	void hidePreRec();
	
	std::vector<Monster*> m_monsterList;
	std::vector<Bullet*> m_monsterBullet;
	std::vector<Monster*> m_shortMonsterList;
	std::vector<Monster*> m_longMonsterList;
	std::map<Vec2, bool> m_monsPosMap;
	std::map<Vec2, bool> m_visitedRoom;


	Entity* m_player = NULL;
	AdventureMapLayer* m_map;
	const int pigNum = 3;
	const int slimeNum = 5;
	const int chiefOfTribeNum = 2;
	const int duckNum = 2;
	const int m_allCheckPoint = 3;

	int m_curCheckPoint;
	int m_dirs[4][2] = { {0,1}, {1,0}, {0,-1},{-1,0} };
	int m_deathMonsNum;
	bool m_fGameOver = false;
	Vec2 m_curRoom;
};
#endif