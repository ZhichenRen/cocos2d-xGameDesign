#include "MonsterManager.h"

bool MonsterManager::init() {
	createMonsters();
	this->scheduleUpdate();
	return true;
}

void MonsterManager::createMonsters()
{
	Monster* monster = NULL;

	Sprite* sprite = NULL;
	for (int i = 0; i < MAX_MONSTER_NUM; i++)
	{
		monster = Monster::create();
		monster->bindSprite(Sprite::create("Slime.png"));
		this->addChild(monster);
		m_monsterArr.pushBack(monster);
	}
}

void MonsterManager::update(float dt)
{
	/*
		µÈ´ýÍæ¼ÒÀàµÇÂ½
	*/
	
	for (auto monster : m_monsterArr)
	{
		monster->show();
		
	}
}

void MonsterManager::wander(Vec2 max)
{
	for (auto monster : m_monsterArr)
	{
		monster->moveTo(Point(rand() % (int)max.x, rand() % (int)max.y));
	}
}