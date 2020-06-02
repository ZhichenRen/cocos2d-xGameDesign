#include "Monster\MonsterManager.h"



void MonsterManager::bindMap(AdventureMapLayer* map)
{
	setManagerMap(map);
	createMonsters();
	createMonsterPos();
	for (auto monster : m_monsterList)
		monster->getMonsterWeapon()->bindMap(map);
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
		monster = Pig::create();
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
			monsWeapon->attack(playerPosition);
			
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
	//auto testVec = this->getMonsterBullets();

}






MonsterManager::MonsterManager()
{
	
}

MonsterManager::~MonsterManager()
{

}