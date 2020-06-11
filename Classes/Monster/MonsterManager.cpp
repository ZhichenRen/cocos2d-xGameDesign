#include "Monster\MonsterManager.h"
#include "Entity\Weapons\TrackWeapon.h"



void MonsterManager::bindMap(AdventureMapLayer* map)
{
	m_map = map;
}

void MonsterManager::bindPlayer(Entity* player)
{
	m_player = player;
	this->scheduleUpdate();
}

void MonsterManager::reviveAllMonsters()
{//有bug
	m_curCheckPoint = 1;
	m_fGameOver = 0;
	m_deathMonsNum = 0;
	for (auto monster : m_monsterList)
	{
		monster->resetPropoties();
		monster->setVisible(true);
	}
	createMonsterPos();
}

void MonsterManager::bindMapForWeapon()
{
	for (auto monster : m_monsterList)
		monster->getMonsterWeapon()->bindMap(m_map);
}

bool MonsterManager::init()
{
	m_curCheckPoint = 1;
	m_deathMonsNum = 0;
	m_fGameOver = 0;
	m_curRoom = ccp(-1, -1);
	return true;
}



void MonsterManager::createMonsterPos()
{//创建怪物位置，在显示怪物之前显示预选框。

	createRandomPos();
	showPreRec();
	auto callback2 = CallFunc::create(
		[this]() {
		hidePreRec();
	}
	);
	auto createAction = Sequence::create(DelayTime::create(2.0f), callback2, NULL);
	runAction(createAction);
}

void MonsterManager::createRandomPos() {
	int k = 0;
	//生成随机野怪
	for (int i = 0; i < m_monsterList.size(); i++)
	{
		auto randInt1 = rand() % 18 + 2;
		auto randInt2 = rand() % 18 + 2;

		auto monsterPos = 32 * ccp(randInt1, randInt2) + ccp(16.5, 0);

		auto worldTar = monsterPos + getPosition();
		Vec2 tarBlock = ccp(static_cast<int>(monsterPos.x) / 21, static_cast<int>(monsterPos.y) / 21);
		if (m_map->isBarrier(worldTar)
			|| m_monsPosMap[tarBlock])//若是障碍物则直接continue
		{
			i--;
			continue;
		}
		if (m_player)
		{
			if (m_player->getPosition() - worldTar < ccp(100, 100) &&
				m_player->getPosition() - worldTar > ccp(-100, -100))
			{//以防一上来就嘲讽
				i--;
				continue;
			}
		}

		m_monsPosMap[tarBlock] = 1;
		m_monsterList[k]->setPosition(monsterPos);

		k++;
	}

	bulkUpRandMons(this->m_bulkMonsterNum);//随机几个怪物变大
}

void MonsterManager::bulkUpRandMons(int totalNum)
{
	int totalBulkMonster = totalNum;
	std::set<int> bulkMap;
	int randMons;
	int monsNum = m_monsterList.size();
	while (1)
	{
		randMons = rand() % monsNum;
		if (bulkMap.count(randMons))
		{
			continue;
		}
		bulkMap.insert(randMons);

		m_monsterList[randMons]->bulkUp();

		totalNum--;
		if (totalNum <= 0)
		{
			break;
		}
	}
}

void MonsterManager::createMonstersWithGiantNum(int giantNum, int totalNum)
{
	//giantNum为0：没有巨大化的怪物
	//giantNum为1以上：有giantNum个巨大化的怪物
	auto randVec = createRandomNums(4, totalNum - 4);
	this->m_bulkMonsterNum = giantNum;
	if (giantNum > totalNum - 4)
	{
		assert("too much giant monsters");
	}
	Pig* pig = NULL;
	Slime* slime = NULL;
	Sprite* sprite = NULL;
	ChiefOfTribe* chiefOfTribe = NULL;
	Duck* duck = NULL;
	//int k = 0;
	for (int i = 0; i < randVec[0] + 1; i++)
	{
		pig = Pig::create();
		pig->bindMap(m_map);
		pig->getMonsterWeapon()->bindMap(m_map);
		pig->bindMonsMgr(this);
		this->addChild(pig);
		m_monsterList.push_back(pig);
		m_shortMonsterList.push_back(pig);
	}

	for (int i = 0; i < randVec[1] + 1; i++)
	{
		duck = Duck::create();
		duck->bindMap(m_map);
		duck->getMonsterWeapon()->bindMap(m_map);
		duck->bindMonsMgr(this);
		this->addChild(duck);
		m_monsterList.push_back(duck);
		m_shortMonsterList.push_back(duck);
	}

	for (int i = 0; i < randVec[2] + 1; i++)
	{
		slime = Slime::create();
		this->addChild(slime);
		slime->bindMap(m_map);
		slime->getMonsterWeapon()->bindMap(m_map);
		slime->bindMonsMgr(this);
		m_monsterList.push_back(slime);
		m_longMonsterList.push_back(slime);
	}

	for (int i = 0; i < randVec[3] + 1; i++)
	{
		chiefOfTribe = ChiefOfTribe::create();
		this->addChild(chiefOfTribe);
		chiefOfTribe->bindMap(m_map);
		chiefOfTribe->getMonsterWeapon()->bindMap(m_map);
		chiefOfTribe->bindMonsMgr(this);
		m_monsterList.push_back(chiefOfTribe);
		m_longMonsterList.push_back(chiefOfTribe);
	}

}

void MonsterManager::createWoodWalls(int woodWallsNum)
{
	//生成随机野怪
	for (int i = 0; i < woodWallsNum; i++)
	{
		auto randInt1 = rand() % 21 ;
		auto randInt2 = rand() % 21 ;

		auto monsterPos = 32 * ccp(randInt1, randInt2) + ccp(16.5, 0);

		auto worldTar = monsterPos + getPosition();
		Vec2 tarBlock = ccp(static_cast<int>(monsterPos.x) / 21, static_cast<int>(monsterPos.y) / 21);
		if (m_map->isBarrier(worldTar)
			|| m_monsPosMap[tarBlock])//若是障碍物则直接continue
		{
			i--;
			continue;
		}
		
		
		m_monsPosMap[tarBlock] = 1;
		auto woodWall = WoodWall::create();
		addChild(woodWall);
		woodWall->bindMonsMgr(this);
		woodWall->bindMap(m_map);
		woodWall->setPosition(monsterPos);
		woodWall->getChildByName("preRect")->setVisible(false);
		m_woodWallList.push_back(woodWall);
	}

}

void MonsterManager::showPreRec()
{
	//auto fadein = FadeIn::create(0.5f);
	for (auto monster : m_monsterList)
	{
		//monster->getChildByName("preRect")->runAction(fadein);
		monster->getChildByName("preRect")->setVisible(true);
		monster->getSprite()->setVisible(false);
		monster->hide();
	}
}

void MonsterManager::hidePreRec()
{
	//auto fadeout = FadeOut::create(0.5f);
	for (auto monster : m_monsterList)
	{
		monster->getChildByName("preRect")->setVisible(false);
		//monster->getChildByName("preRect")->runAction(fadeout);
		monster->getSprite()->setVisible(true);
		monster->show();
	}
}

std::vector<int> MonsterManager::createRandomNums(int numCnt, int sum)
{
	std::vector<int> randomVec;
	int randNum;
	numCnt -= 1;
	while (numCnt--)
	{
		randNum = rand() % sum;
		randomVec.push_back(randNum);
		sum -= randNum;
	}
	randomVec.push_back(sum);
	return randomVec;
}

bool MonsterManager::resetAllMons()
{
	m_deathMonsNum = 0;//清零
	m_curCheckPoint++;
	if (m_curCheckPoint >= m_allCheckPoint)
	{
		m_fGameOver = 1;
		return false;
	}
	for (auto monster : m_monsterList)
	{
		monster->resetPropoties();
	}
	createMonsterPos();
	return true;
}

bool MonsterManager::isGameOver()
{
	if (!m_fIsInited)
		return true;
	return m_fGameOver;
}


void MonsterManager::setInited()
{
	m_fIsInited = 1;
}


bool MonsterManager::getInited()
{
	return m_fIsInited;
}


void MonsterManager::update(float dt)
{
	if (!m_fIsInited)
		return;
	Point playerPosition = m_player->getPosition() - getPosition();
	//相对坐标的转化
	//playerPosition = convertToNodeSpace(playerPosition);
	if (m_deathMonsNum == m_monsterList.size())
	{

		resetAllMons();
	}

	for (auto woodWall : m_woodWallList)
	{
		auto curPos = woodWall->getPosition();
		Vec2 blockOccupied = ccp(static_cast<int>(curPos.x) / 21, static_cast<int>(curPos.y) / 21);
		if (!woodWall->isAlive())
		{
			continue;
		}
		if (woodWall->getHp() <= 0) //更新活着的状态
		{
			m_monsPosMap[blockOccupied] = 0;//清除位置信息
			woodWall->die();
		}
	}

	if (m_fGameOver)//游戏结束了
	{
		return;
	}
	for (auto monster : m_monsterList)
	{
		auto curPos = monster->getPosition();
		Vec2 blockOccupied = ccp(static_cast<int>(curPos.x) / 21, static_cast<int>(curPos.y) / 21);
		auto dis = sqrtf(pow(playerPosition.x - curPos.x, 2) + pow(playerPosition.y - curPos.y, 2));
		if (monster->isAlive())
		{
			if (monster->getHp() <= 0) //更新活着的状态
			{
				m_monsPosMap[blockOccupied] = 0;//清除位置信息
				monster->die();
				m_deathMonsNum++;
				continue;
			}



			if (dis < 200)//200是嘲讽范围
			{
				monster->setMonsTaunted();
			}

			if (!monster->isTaunted())//若未被嘲讽
			{
				monster->wander();
				continue;
			}

			auto monsWeapon = monster->getMonsterWeapon();
			if (dis < 2 * monsWeapon->getRange())//两倍距离以内再攻击
				//攻击要用到地图中的坐标。
			{
				if (typeid(*monsWeapon) == typeid(TrackWeapon))
				{
					dynamic_cast<TrackWeapon*>(monsWeapon)->bindPlayer(m_player);
				}
				monsWeapon->attack(m_map->convertToWorldSpace(m_player->getPosition()));
			}


			m_monsPosMap[blockOccupied] = 0;
			//建立走位后的信息

			float xDirToMove = curPos.x > playerPosition.x ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();
			float yDirToMove = curPos.y > playerPosition.y ? -monster->getMonsterSpeed() : monster->getMonsterSpeed();


			if (abs(curPos.x - playerPosition.x) < 3)	xDirToMove = 0;
			if (abs(curPos.y - playerPosition.y) < 3)	yDirToMove = 0;//若差距不大则不走位了

			auto posToMove = ccp(curPos.x + xDirToMove, curPos.y + yDirToMove);

			//探测周围有没有同类
			int i = 0;
			while (!monster->mySetPosition(posToMove)
				&& i++ < 4)
			{
				posToMove = ccp(curPos.x + m_dirs[i][0] * xDirToMove, curPos.y + m_dirs[i][1] * yDirToMove);
				//以防怪物卡墙
			}
		}
	}

	
}


std::vector<Bullet*> MonsterManager::getMonsterBullets() const
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

std::vector<Monster*> MonsterManager::getWoodWall() const
{
	return m_woodWallList;
}

void MonsterManager::setPosMap(Vec2 pos, bool flag)
{
	m_monsPosMap[pos] = flag;
}

bool MonsterManager::isPosOccupied(Vec2 pos)
{
	return m_monsPosMap[pos];
}

void MonsterManager::setCurRoom(Vec2 curRoom)
{
	m_curRoom = curRoom;
}

Vec2 MonsterManager::getCurRoom()
{
	return m_curRoom;
}

void MonsterManager::markRoomVisited(Vec2 room)
{
	m_visitedRoom[room] = true;
}

bool MonsterManager::isRoomVisited(Vec2 room)
{
	return m_visitedRoom[room];
}
void MonsterManager::setBulkMonsterNum(int giantNum)
{
	m_bulkMonsterNum = giantNum;
}