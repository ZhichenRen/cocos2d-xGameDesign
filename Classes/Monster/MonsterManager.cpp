#include "Monster\MonsterManager.h"



void MonsterManager::bindMap(AdventureMapLayer* map)
{
	setManagerMap(map);
	createMonsters();
	createMonsterPos();

	return;
}

void MonsterManager::bindPlayer(Sprite* player)
{
	setPlayer(player);
	this->scheduleUpdate();
}

bool MonsterManager::init() {
	
	return true;
}

void MonsterManager::createMonsters()
{
	Monster* monster = NULL;
	Sprite* sprite = NULL;
	int k = 0;
	
	for (int i = 0; i < 50; i++)
	{
		monster = Slime::create();
		this->addChild(monster);
		m_monsterList.push_back(monster);
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
		//srand(unsigned int(time));
		int randInt = ranF * 441;		
		auto monsterPos = Vec2(randInt % 21 , randInt / 21);
		log("The block is %f, %f", monsterPos.x, monsterPos.y);
		if (curMap.count(monsterPos))//若是障碍物则直接continue
		{
			i--;
			continue;
		}
		monsterPos.x *= 32;
		monsterPos.y *= 32;
		monsterPos = m_map->convertToMapSpace(convertToWorldSpace(monsterPos));
		m_monsterList[k]->setPosition(monsterPos);
		log("%f,%f", m_monsterList[k]->getPosition().x, m_monsterList[k]->getPosition().y);
		k++;
	}
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
			//monsWeapon->attack(m_map->convertToMapSpace(convertToWorldSpace(playerPosition)));
			auto curPos = monster->getPosition();
			float xFlag = curPos.x > playerPosition.x ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			float yFlag = curPos.y > playerPosition.y ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			if (abs(curPos.x - playerPosition.x) < 20)	xFlag = 0;
			if (abs(curPos.y - playerPosition.y) < 20)	yFlag = 0;
			//monster->moveTo(ccp(curPos.x + xFlag,curPos.y + yFlag));
			if (!m_map->isBarrier(m_map->convertToMapSpace(convertToWorldSpace(ccp(curPos.x + xFlag,	curPos.y + yFlag)))))
				monster->setPosition(ccp(curPos.x + xFlag,
					curPos.y + yFlag));
		}
	}
}






MonsterManager::MonsterManager()
{
	
}

MonsterManager::~MonsterManager()
{
}