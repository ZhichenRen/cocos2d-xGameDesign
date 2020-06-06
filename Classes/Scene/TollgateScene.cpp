#include "Scene/TollgateScene.h"
#include "Scene/PauseScene.h"
#include "Entity/Weapons/Bullets/ExplosiveBullet.h"
#include "Entity/Weapons/RPG.h"
#include "Entity/Weapons/Shotgun.h"

USING_NS_CC;

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
	this->addChild(m_map, 0, 100);//游戏地图 tag�?00

}

void TollgateScene::addPlayer()
{
	TMXObjectGroup* group = m_map->getMap()->getObjectGroup("objects");//获取对象�?
	ValueMap spawnPoint = group->getObject("hero");//根据hero对象的位置放置精�?
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
	playerController->setIsRanger(typeid(*m_player) == typeid(Ranger));//以后与memberSelect结合
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


void TollgateScene::loadMonsters()
{
	monsterMgr = MonsterManager::create();
	auto playerPos = this->convertToNodeSpace(m_player->getPosition());
	playerPos.x -= 10 * 32;
	playerPos.y -= 10 * 32;
	monsterMgr->setPosition(playerPos);
	monsterMgr->bindMap(m_map);
	monsterMgr->bindPlayer(static_cast<Entity*>(this->m_player));
	

	
	m_map->addChild(monsterMgr, 2);
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
	auto miniMapLayer = miniMap->getLayer("miniMapLayer");
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);

	miniMap->setPosition(playerPos + Vec2(200, 50));

	if (roomCoord == Vec2(-1, -1))
	{
		return;
	}

	miniMapLayer->setTileGID(2, 2 * lastRoomCoord);//原房间浅�?
	miniMapLayer->setTileGID(1, 2 * Vec2(roomCoord.y, roomCoord.x));//现房间深�?

	if (lastRoomCoord != Vec2(roomCoord.y, roomCoord.x))
	{
		if (lastRoomCoord.x == roomCoord.y)//上下相连
		{
			miniMapLayer->setTileGID(4, lastRoomCoord + Vec2(roomCoord.y, roomCoord.x));
		}
		else//左右相连
		{
			miniMapLayer->setTileGID(3, lastRoomCoord + Vec2(roomCoord.y, roomCoord.x));
		}
	}
	lastRoomCoord = Vec2(roomCoord.y, roomCoord.x);
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

	auto roomCoord = m_map->roomCoordFromPosition(playerPos);//房间坐标
	auto roomNum = roomCoord.x * 5 + roomCoord.y;//房间序号

	Vec2 dir[4] = { {0,1},{0,-1},{1,0},{-1,0} };//四个方向

	if (true)//进入有怪物的房间，开始战�?
	{
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
		if (monsterMgr->isGameOver())//结束战斗
		{
			for (auto elem : dirVec)
			{
				AdventureMapLayer::switchGate(wall, barrier, roomNum, elem, false);
			}
		}
	}

	//��ײ���
	auto player_bullet = m_player->getBullet();
	auto monsters_bullet = monsterMgr->getMonsterBullets();
	auto monsters = monsterMgr->getMonster();

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
					monster->hit(bullet->getDamage(), bullet->getDegree());
					monster->setTaunted(1);
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
									unlucky_monster->hit(explosive_bullet->getExplosionDamage(), explosive_bullet->getDegree());
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
}