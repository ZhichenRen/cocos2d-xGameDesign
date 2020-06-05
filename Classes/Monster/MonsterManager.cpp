#include "Monster\MonsterManager.h"



void MonsterManager::bindMap(AdventureMapLayer* map)
{
	m_map = map;
	createMonsters();
	createMonsterPos();
	for (auto monster : m_monsterList)
		monster->getMonsterWeapon()->bindMap(map);
	return;
}

void MonsterManager::bindPlayer(Sprite* player)
{
	m_player = player;
	this->scheduleUpdate();
}

bool MonsterManager::init() 
{
	m_checkPoint = 1;
	m_deathMonsNum = 0;
	return true;
}

void MonsterManager::createMonsters()
{
	Pig* pig = NULL;
	Slime* slime = NULL;
	Sprite* sprite = NULL;
	int k = 0;
	
	for (int i = 0; i < this->pigNum; i++)
	{
		pig = Pig::create();
		this->addChild(pig);
		m_monsterList.push_back(pig);
		m_shortMonsterList.push_back(pig);
	}

	for (int i = 0; i < this->slimeNum; i++)
	{
		slime = Slime::create();
		this->addChild(slime);
		m_monsterList.push_back(slime);
		m_longMonsterList.push_back(slime);
	}
}

void MonsterManager::createMonsterPos() 
{
	auto size = Size(19 * 32, 19 * 32);
	int k = 0;
	//生成随机野怪
	auto curMap = m_map->getBarrierMap();
	for (int i = 0; i < m_monsterList.size(); i++)
	{
		auto ranF = CCRANDOM_0_1();
		int randInt = ranF * 441;		
		auto monsterPos = Vec2(randInt % 21 , randInt / 21);
		if (curMap.count(monsterPos))//若是障碍物则直接continue
		{
			i--;
			continue;
		}
		m_monsPosMap[monsterPos] = 1;
		monsterPos.x *= 32;
		monsterPos.y *= 32;
		m_monsterList[k]->setPosition(monsterPos);
		k++;
	}
}

void MonsterManager::resetAllMons()
{
	m_deathMonsNum = 0;//清零
	for (auto monster : m_monsterList)
	{
		monster->resetPropoties();
	}
	createMonsterPos();
}


void MonsterManager::update(float dt)
{
	Point playerPosition = this->convertToNodeSpace(m_map->convertToWorldSpace(m_player->getPosition()));
	//相对坐标的转化
	//playerPosition = convertToNodeSpace(playerPosition);
	if (m_deathMonsNum == m_monsterList.size())
	{
		resetAllMons();
	}
	for (auto monster : m_monsterList)
	{
		auto curPos = monster->getPosition();
		Vec2 blockOccupied = ccp(static_cast<int>(curPos.x) / 21, static_cast<int>(curPos.y) / 21);
		if (monster->isAlive())
		{
			if (monster->getHp() < 0)
			{
				m_monsPosMap[blockOccupied] = 0;//清除位置信息
				monster->die();
				m_deathMonsNum++;
				continue;
			}
			auto monsWeapon = monster->getMonsterWeapon(); 
			
			//auto curAbsPos = convertToWorldSpace( monster->getPosition());
			


			auto dis = sqrtf(pow(playerPosition.x - curPos.x, 2) + pow(playerPosition.y - curPos.y, 2));
			if (dis < 2 * monsWeapon->getRange())//两倍距离以内再攻击
				//攻击要用到地图中的坐标。
				monsWeapon->attack(m_map->convertToWorldSpace(m_player->getPosition()));

			

			m_monsPosMap[blockOccupied] = 0;
			//建立走位后的信息
			
			float xDirToMove = curPos.x > playerPosition.x ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			float yDirToMove = curPos.y > playerPosition.y ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();

			
			if (abs(curPos.x - playerPosition.x) < 5)	xDirToMove = 0;
			if (abs(curPos.y - playerPosition.y) < 5)	yDirToMove = 0;//若差距不大则不走位了

			auto posToMove = ccp(curPos.x + xDirToMove, curPos.y + yDirToMove);

			//探测周围有没有同类
			for (int i = 0; i < 4; i++)
			{
				
				auto tmp = ccp(blockOccupied.x + m_dirs[i][0], blockOccupied.y + m_dirs[i][1]);
				if (m_monsPosMap[tmp])//如果该位置有敌人，就往反方向退
				{
					posToMove.x -= 2 * m_dirs[i][0] * xDirToMove;
					posToMove.y -= 2 * m_dirs[i][0] * yDirToMove;
					break;
				}

			}
			//monster->moveTo(ccp(curPos.x + xDirToMove,curPos.y + yDirToMove));
			if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(posToMove)))
				&&!m_monsPosMap[blockOccupied])
					//如果没有障碍就可以向这个位置奔跑
			{
				
				monster->setPosition(posToMove);
			}
			else
			{
				auto differ = posToMove - curPos;
				posToMove -= 2 * differ;
				monster->setPosition(posToMove);
			}//还是会卡墙

			///////////////卡墙现象最后应该修复
			blockOccupied = ccp(static_cast<int>(posToMove.x) / 21, static_cast<int>(posToMove.y) / 21);
			m_monsPosMap[blockOccupied] = 1;
		}
		else
		{

		}
	}
}






MonsterManager::MonsterManager()
{
	
}

MonsterManager::~MonsterManager()
{

}

std::vector<Bullet*> MonsterManager::getMonsterBullets()
{
	std::vector<Bullet*> monsterBullets;
	for (auto monster : m_monsterList)
	{
		auto tmpBlt = monster->getMonsterWeapon()->getBullet();//获取每个怪物的武器发射出的子弹
		for (auto blt : tmpBlt)
			monsterBullets.push_back(blt);//将子弹塞进向量
	}
	return monsterBullets;
}

std::vector<Monster*> MonsterManager::getMonster()const
{
	return m_monsterList;
}