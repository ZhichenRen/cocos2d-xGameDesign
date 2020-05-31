#include "Monster\MonsterManager.h"



void MonsterManager::bindMap(AdventureMapLayer* map)
{
	setManagerMap(map);
	createMonsters();
	createMonsterPos();
	return;
}

bool MonsterManager::init() {
	this->scheduleUpdate();
	return true;
}

void MonsterManager::createMonsters()
{
	Monster* monster = NULL;
	Sprite* sprite = NULL;
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			monster = Slime::create();
			//monster->bindSprite(Sprite::create(monster->getResTrack()));
			this->addChild(monster);
			m_monsterList.push_back(monster);
		}
	}
}

void MonsterManager::createMonsterPos() 
{
	auto size = this->m_map->getContentSize();
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			
			auto curPos = ccp(size.width * i / 4, size.height * j / 4);
			curPos = m_map->convertToMapSpace(convertToWorldSpace(curPos));
			m_monsterList[k]->setPosition(curPos);
			log("%f,%f",m_monsterList[k]->getPosition().x, m_monsterList[k]->getPosition().y);
			k++;
			//log("WorldPos: %f,%f", m_monsterList.at(k)->getPosition().x, m_monsterList.at(k++)->getPosition().y);
		}
	}
}
void MonsterManager::update(float dt)
{
	auto size = this->m_map->getContentSize();
	int SizeX = size.width / 2;
	int SizeY = size.height / 2;
	for (auto monster : m_monsterList)
	{
		
		if (monster->isAlive())
		{
			log("WorldPos: %f,%f", monster->getPosition().x, monster->getPosition().y);
			if (monster->getHp() < 0)
			{
				monster->die();
				continue;
			}
			//auto monsWeapon = monster->getMonsterWeapon(); 
			////monsWeapon->attack(Point(SizeX, SizeY));
			//auto curPos = monster->getPosition();
			//curPos = m_map->convertToMapSpace(convertToWorldSpace(curPos));
			//log("NodePos: %f,%f", curPos.x, curPos.y);
			//float xFlag = curPos.x > SizeX ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			//float yFlag = curPos.y > SizeY ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			//if (abs(curPos.x - SizeX) < 20)	xFlag = 0;
			//if (abs(curPos.y - SizeY) < 20)	yFlag = 0;
			////monster->moveTo(ccp(curPos.x + xFlag,curPos.y + yFlag));
			//monster->setPosition(ccp(curPos.x + xFlag,
			//	curPos.y + yFlag));
		}
	}
}






MonsterManager::MonsterManager()
{
	
}

MonsterManager::~MonsterManager()
{
}