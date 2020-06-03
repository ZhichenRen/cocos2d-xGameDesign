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

bool MonsterManager::init() {
	
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
		monsterPos = m_map->convertToMapSpace(convertToWorldSpace(monsterPos));
		m_monsterList[k]->setPosition(monsterPos);
		//log("%f,%f", m_monsterList[k]->getPosition().x, m_monsterList[k]->getPosition().y);
		k++;
	}
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

void MonsterManager::update(float dt)
{
	Point playerPosition = m_player->getPosition();
	playerPosition.x -= this->getPosition().x;
	playerPosition.y -= this->getPosition().y;
	for (auto monster : m_monsterList)
	{
		if (monster->isAlive())
		{
			if (monster->getHp() < 0)
			{
				monster->die();
				continue;
			}
			auto monsWeapon = monster->getMonsterWeapon(); 
			
			auto curPos = monster->getPosition();
			
			auto dis = sqrtf(pow(playerPosition.x - curPos.x, 2) + pow(playerPosition.y - curPos.y, 2));
			if (dis < 2 * monsWeapon->getRange())//两倍距离以内再攻击
				monsWeapon->attack(playerPosition);

			Vec2 blockOccupied = ccp(static_cast<int>(curPos.x) / 21, static_cast<int>(curPos.y) / 21);

			m_monsPosMap[blockOccupied] = 0;
			//建立走位后的信息
			
			float xDirToMove = curPos.x > playerPosition.x ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			float yDirToMove = curPos.y > playerPosition.y ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();

			
			if (abs(curPos.x - playerPosition.x) < 5)	xDirToMove = 0;
			if (abs(curPos.y - playerPosition.y) < 5)	yDirToMove = 0;//若差距不大则不走位了

			curPos.x += xDirToMove;
			curPos.y += yDirToMove;


			blockOccupied = ccp(static_cast<int>(curPos.x) / 21, static_cast<int>(curPos.y) / 21);
			//monster->moveTo(ccp(curPos.x + xDirToMove,curPos.y + yDirToMove));
			if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(curPos)))
			&&	!m_monsPosMap[blockOccupied])
				monster->setPosition(curPos);
			m_monsPosMap[blockOccupied] = 1;
		}
	}
}






MonsterManager::MonsterManager()
{
	
}

MonsterManager::~MonsterManager()
{

}