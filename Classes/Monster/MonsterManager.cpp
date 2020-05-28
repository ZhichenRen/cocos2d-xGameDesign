#include "Monster\MonsterManager.h"



bool MonsterManager::init() {
	createMonsters();
	createMonsterPos();
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
			m_monsterList.pushBack(monster);
		}
	}
}

void MonsterManager::createMonsterPos() 
{
	auto size = Director::getInstance()->getVisibleSize();
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m_monsterList.at(k++)->setPosition((Vec2( size.width * i / 4, size.height * j / 4 )));
		}
	}
}
void MonsterManager::update(float dt)
{
	auto size = Director::getInstance()->getVisibleSize();
	int SizeX = size.width / 2;
	int SizeY = size.height / 2;
	
	for (auto monster : m_monsterList)
	{
		
		if (monster->isAlive())
		{
			if (monster->getHp() < 0)
			{
				monster->die();
				continue;
			}
			//monster->setHp(monster->getHp() - 1);
			auto monsWeapon = monster->getMonsterWeapon(); 
			monsWeapon->attack(Point(SizeX, SizeY));
			//auto monsPos = monster->getPosition();
			auto curPos = convertToNodeSpace ( convertToWorldSpace(monster->getPosition()));
			float xFlag = curPos.x > SizeX ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			float yFlag = curPos.y > SizeY ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			if (abs(curPos.x - SizeX) < 20)	xFlag = 0;
			if (abs(curPos.y - SizeY) < 20)	yFlag = 0;
			monster->moveTo(ccp(curPos.x + xFlag,
				curPos.y + yFlag));
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