#include "MonsterManager.h"

std::vector<Vec2> tmp;
bool MonsterManager::init() {
	auto size = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tmp.push_back(Vec2(size.width * i / 4, size.height * j / 4));
		}
	}
	createMonsters();
	this->scheduleUpdate();
	return true;
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
			Vec2 curPos = monster->getPosition();
			float xFlag = curPos.x > SizeX ? -monster->getSpeed() : monster->getSpeed();
			float yFlag = curPos.y > SizeY ? -monster->getSpeed() : monster->getSpeed();
			if (curPos.x == SizeX)	xFlag = 0;
			if (curPos.y == SizeY)	yFlag = 0;
			monster->moveTo(Vec2(curPos.x + xFlag,
				curPos.y + yFlag));
		}
		else
			monster->show();
	}
}






MonsterManager::MonsterManager()
{
	m_fShowTimeCount = 0;
}

MonsterManager::~MonsterManager()
{
}

//bool MonsterManager::initWithLevel(int iCurLevel)
//{
//	createMonsters(iCurLevel);
//	return true;
//}
//
void MonsterManager::createMonsters()
{
	Monster* monster = NULL;
	Sprite* sprite = NULL;
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			monster = Monster::create();
			monster->bindSprite(Sprite::create("Slime.png")); 
			monster->setPosition(tmp[k++]);
			this->addChild(monster);
			m_monsterList.pushBack(monster);
		}
	}
}



//int MonsterManager::getNotShowMonsterCount()
//{
//	return m_notShowMonsterList.size();
//}

//Vector<Monster*> MonsterManager::getMonsterList()
//{
//	return m_monsterList;
//}

//MonsterPos* MonsterManager::getMonsterEndPos()
//{
//	return nullptr;
//}

//MonsterPos* MonsterManager::getMonsterStartPos() {
//	return (MonsterPos*)m_monsterPosList.at(0);
//}
//
//MonsterPos* MonsterManager::getMonsterEndPos() {
//	return (MonsterPos*)m_monsterPosList.at(m_monsterPosList.size() - 1);
//}


void MonsterManager::showMonster(float dt) 
{
	
}