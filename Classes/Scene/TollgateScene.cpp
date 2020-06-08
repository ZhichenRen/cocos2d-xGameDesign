#include "Scene/TollgateScene.h"
#include "Scene/PauseScene.h"
#include "Entity/Weapons/Bullets/ExplosiveBullet.h"
#include "Entity/Weapons/RPG.h"
#include "Entity/Weapons/Shotgun.h"

USING_NS_CC;

extern int coinNum;

Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	Director::getInstance()->setProjection(Director::Projection::_2D);
	return scene;
}

void TollgateScene::loadMap()
{
	m_map = AdventureMapLayer::create();
	this->addChild(m_map, 0, 100);//娓告垙鍦板浘 tag涓?00

}

void TollgateScene::addPlayer()
{
	TMXObjectGroup* group = m_map->getMap()->getObjectGroup("objects");//鑾峰彇瀵硅薄灞?
	ValueMap spawnPoint = group->getObject("hero");//鏍规嵁hero瀵硅薄鐨勪綅缃斁缃簿鐏?
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	m_player = Ranger::create();
	m_player->setPosition(Vec2(x, y));

	m_player->setTiledMap(m_map);
	m_player->setCdBar(m_cdBar);
	m_map->addChild(m_player, 2, 200);
}

void TollgateScene::addLongRangeWeapon()
{
	m_player->setLongRange(Shotgun::create());
}

void TollgateScene::loadController()
{
	auto animate = m_player->stand();
	auto* playerController = PlayerController::create();
	playerController->setiXSpeed(0);
	playerController->setiYSpeed(0);
	this->addChild(playerController);
	m_player->setController(playerController);
	playerController->setPlayer(m_player);
	playerController->setIsRanger(typeid(*m_player) == typeid(Ranger));//浠ュ悗涓巑emberSelect缁撳悎
	playerController->setStandAnimate(animate);

}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;

	this->scheduleUpdate();

	loadMap();
	loadUI();
	addPlayer();
	//addLongRangeWeapon();
	loadController();
	loadMonsters();
	loadListeners();

	return true;
}

void TollgateScene::onEnter()
{
	Layer::onEnter();
	loadUI();
	addLongRangeWeapon();
	//loadListeners();
}

void TollgateScene::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("INGAME_1.ExportJson");
	this->addChild(UI, 0, 0);
	m_cdBar = (LoadingBar*)Helper::seekWidgetByName(UI, "ability_loading_bar");

	/*auto pause_button = (Button*)Helper::seekWidgetByName(UI, "pause_button");
	pause_button->addTouchEventListener(this, toucheventselector(HelloWorld::pauseEvent));*/
}




const int coord[25][2] = {
		{11,11},{52,11},{93,11},{134,11},{175,11},
		{11,52},{52,52},{93,52},{134,52},{175,52},
		{11,93},{52,93},{93,93},{134,93},{175,93},
		{11,134},{52,134},{93,134},{134,134},{175,134},
		{11,175},{52,175},{93,175},{134,175},{175,175} };//25个房间的中心坐标

void TollgateScene::loadMonstersInNewRoom()
{
	auto roomCoord = m_monsterMgr->getCurRoom();
	m_monsterMgr->markRoomVisited(roomCoord);
	auto midPoint = ccp(coord[static_cast<int>(5 * roomCoord.x + roomCoord.y)][0],
		coord[static_cast<int>(5 * roomCoord.x + roomCoord.y)][1]);
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10,- 10)) * 32;
	log("current room is%f, %f\n", roomCoord.x, roomCoord.y);
	log("LUPoint  is%f, %f\n", LUPoint.x, LUPoint.y);
	m_monsterMgr->setPosition(LUPoint);
	
	m_monsterMgr->reviveAllMonsters();
}


void TollgateScene::loadMonsters()
{
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);
	
	m_monsterMgr = MonsterManager::create();
	m_monsterMgr->markRoomVisited(roomCoord);
	m_monsterMgr->setCurRoom(roomCoord);
	auto midPoint = ccp( coord[static_cast<int>(5 * roomCoord.x + roomCoord.y)][0] ,
		coord[static_cast<int>(5 * roomCoord.x + roomCoord.y)][1]);
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10, -10)) * 32;
	m_monsterMgr->setPosition(LUPoint);
	m_monsterMgr->bindMap(m_map);
	m_monsterMgr->bindPlayer(static_cast<Entity*>(this->m_player));
	m_map->addChild(m_monsterMgr, 2);
}

void TollgateScene::loadListeners()
{
	auto pause_listener = EventListenerKeyboard::create();
	pause_listener->onKeyPressed = [](EventKeyboard::KeyCode key, Event* event)
	{
		return true;
	};
	pause_listener->onKeyReleased = [=](EventKeyboard::KeyCode key, Event* event)
	{
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_E:
			if (m_player->getPosition() < m_map->getChest()->getPosition() + Vec2(50, 50) &&
				m_player->getPosition() > m_map->getChest()->getPosition() - Vec2(50, 50))
			{
				m_map->getChest()->setVisible(false);
				m_player->setLongRange(RPG::create());
			}
			else if (m_player->getPosition() < m_map->getShop()->getPosition() + Vec2(50, 50) &&
				m_player->getPosition() > m_map->getShop()->getPosition() - Vec2(50, 50))
			{
				coinNum -= 20;
				m_player->setLongRange(RPG::create());
			}
			else if (m_player->getPosition() < m_map->getPortal()->getPosition() + Vec2(50, 50) &&
				m_player->getPosition() > m_map->getPortal()->getPosition() - Vec2(50, 50))
			{
				//auto layer = TollgateScene::create();
				//this->addChild(layer);
				auto scene = TollgateScene::createScene();
				Director::getInstance()->replaceScene(scene);
			}
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Size visible_size = Director::getInstance()->getVisibleSize();
			CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
			background->begin();
			this->visit();
			background->end();
			Director::getInstance()->pushScene(PauseScene::createScene(background));
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pause_listener, this);
}

Vec2 lastRoomCoord(2, 2);

void TollgateScene::updateMiniMap(TMXTiledMap* miniMap)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto miniMapLayer = miniMap->getLayer("miniMapLayer");
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);

	miniMap->setPosition(m_map->convertToNodeSpace(this->getPosition()) + Vec2(700, 400));

	if (roomCoord == Vec2(-1, -1))
	{
		return;
	}

	miniMapLayer->setTileGID(2, 2 * lastRoomCoord);//鍘熸埧闂存祬鐏?
	miniMapLayer->setTileGID(1, 2 * Vec2(roomCoord.y, roomCoord.x));//鐜版埧闂存繁鐏?

	if (lastRoomCoord != Vec2(roomCoord.y, roomCoord.x))
	{
		if (lastRoomCoord.x == roomCoord.y)//涓婁笅鐩歌繛
		{
			miniMapLayer->setTileGID(4, lastRoomCoord + Vec2(roomCoord.y, roomCoord.x));
		}
		else//宸﹀彸鐩歌繛
		{
			miniMapLayer->setTileGID(3, lastRoomCoord + Vec2(roomCoord.y, roomCoord.x));
		}
	}
	lastRoomCoord = Vec2(roomCoord.y, roomCoord.x);
}

void TollgateScene::updateCoinNum()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto n = this->getChildByTag(101);
	if (n)
	{
		this->removeChildByTag(101);
	}
	auto num = __String::createWithFormat("%d", coinNum);
	auto coinLabel = Label::createWithTTF(num->getCString(), "fonts/arial.ttf", 30);

	coinLabel->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 600));
	this->addChild(coinLabel, 20, 101);
}

void TollgateScene::update(float dt)
{
	auto playerPos = m_player->getPosition();
	auto barrier = m_map->getCollidable();
	auto map = m_map->getMap();
	auto miniMap = m_map->getMiniMap();
	auto wall = m_map->getWall();
	auto roadPairs = m_map->getRoadPairs();
	updateMiniMap(miniMap);

	updateCoinNum();

	auto roomCoord = m_map->roomCoordFromPosition(playerPos);//鎴块棿鍧愭爣
	auto roomNum = roomCoord.x * 5 + roomCoord.y;//鎴块棿搴忓彿
	if (m_map->isMonsterRoom(roomCoord)	//首先它得是个怪物房间
		&&!m_monsterMgr->isRoomVisited(roomCoord))//其次它没有被到访过
	{
		m_monsterMgr->setCurRoom(roomCoord);
		loadMonstersInNewRoom();
	}
	Vec2 dir[4] = { {0,1},{0,-1},{1,0},{-1,0} };//鍥涗釜鏂瑰悜

	if (true)//杩涘叆鏈夋�墿鐨勬埧闂达紝寮�濮嬫垬鏂?
	{
		miniMap->setVisible(false);
		std::vector<int>dirVec;
		for (int i = 0; i < 4; i++)
		{
			for (auto elem : roadPairs)
			{
				if (elem.first == roomCoord && elem.second == dir[i] + roomCoord ||
					elem.second == roomCoord && elem.first == dir[i] + roomCoord)
				{
					dirVec.push_back(i);
				}
			}
		}
		for (auto elem : dirVec)
		{
			AdventureMapLayer::switchGate(wall, barrier, roomNum, elem, true);
		}
		//auto t = time(nullptr);
		if (m_monsterMgr->isGameOver())//缁撴潫鎴樻枟
		{
			for (auto elem : dirVec)
			{
				AdventureMapLayer::switchGate(wall, barrier, roomNum, elem, false);
			}
			miniMap->setVisible(true);
		}
	}

	//碰撞检测
	auto player_bullet = m_player->getBullet();
	auto monsters_bullet = m_monsterMgr->getMonsterBullets();
	auto monsters = m_monsterMgr->getMonster();

	//player bullet
	for (auto bullet : player_bullet)
	{
		//cocos2d::Point bullet_pos = convertToWorldSpace(bullet->getPosition());
		//if (m_map->isBarrier(bullet_pos))
		//{
		//	if (typeid(*bullet) == typeid(ExplosiveBullet))
		//	{
		//		auto explosive_bullet = dynamic_cast<ExplosiveBullet*>(bullet);
		//		explosive_bullet->explode();
		//		for (auto unlucky_monster : monsters)
		//		{
		//			if (unlucky_monster->isAlive())
		//			{
		//				cocos2d::Point explosive_origin_point = convertToWorldSpace(explosive_bullet->getPosition());
		//				if (unlucky_monster->getBoundingBox().intersectsCircle(explosive_origin_point, explosive_bullet->getExplosionRange()))
		//				{
		//					unlucky_monster->hit(explosive_bullet->getExplosionDamage());
		//				}
		//			}
		//		}
		//	}
		//	bullet->setIsUsed(true);
		//}
		for (auto monster : monsters)
		{
			if (monster->isAlive())
			{
				if (bullet->isCollideWith(monster))
				{
					monster->hit(bullet->getDamage(), bullet->getDegree(), 1);
					
					if (typeid(*bullet) == typeid(ExplosiveBullet))
					{
						auto explosive_bullet = dynamic_cast<ExplosiveBullet*>(bullet);
						explosive_bullet->explode();
						for (auto unlucky_monster : monsters)
						{
							if (unlucky_monster->isAlive())
							{
								cocos2d::Point explosive_origin_point = m_map->convertToWorldSpace(explosive_bullet->getPosition());
								if (unlucky_monster->getBoundingBox().intersectsCircle(explosive_origin_point, explosive_bullet->getExplosionRange()))
								{
									unlucky_monster->hit(explosive_bullet->getExplosionDamage(), explosive_bullet->getDegree(), 1);
								}
							}
						}
					}
					bullet->setIsUsed(true);
				}
			}
		}			
	}

	//monster bullet
	for (auto bullet : monsters_bullet)
	{
		if (bullet->isCollideWith(m_player))
		{
			m_player->hit(bullet->getDamage());
			bullet->setIsUsed(true);
		}
	}

	for (auto coin : m_map->getCoinList())
	{
		if (coin->getPosition() > m_player->getPosition() - Vec2(10, 10) &&
			coin->getPosition() < m_player->getPosition() + Vec2(10, 10) && 
			coin->isVisible())
		{
			coin->setVisible(false);
			coinNum++;
		}
	}
}