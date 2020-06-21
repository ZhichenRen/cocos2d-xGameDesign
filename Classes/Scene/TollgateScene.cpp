#include <string>
#include "Scene/TollgateScene.h"
#include "Scene/SafeMapScene.h"
#include "Scene/PauseScene.h"
#include "Scene/HomeScene.h"
#include "Entity/Item/Player/Priest/Priest.h"
#include "Entity/Item/Player/Knight/Knight.h"
#include "Entity/Weapons/Bullets/ExplosiveBullet.h"
#include "Entity/Weapons/RPG.h"
#include "Entity\Weapons\GoldenSword.h"
#include "Entity/Weapons/Shotgun.h"
#include "GameData.h"
#include "Scene/DeathScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/FinishScene.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;
using namespace CocosDenshion;
restrorePlayer restore;

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	m_map = AdventureMapLayer::create();
	this->addChild(m_map, 0, 100);
	m_map->getMiniMap()->setPosition(Vec2(origin.x + visibleSize.width - 300, origin.y + visibleSize.height - 400));
	this->addChild(m_map->getMiniMap(), 0, 10101);
}

void TollgateScene::addPlayer()
{
	TMXObjectGroup* group = m_map->getMap()->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("hero");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	
	if(SafeMapLayer::whichPlayer()==1)
	    m_player = Ranger::create();
	else if(SafeMapLayer::whichPlayer() == 2)
		m_player = Priest::create();
	else
		m_player = Knight::create();
	m_player->setPosition(Vec2(x, y));

	m_player->setTiledMap(m_map);
	m_player->setCdBar(m_cdBar);
	m_player->setHpBar(m_hpBar);
	m_player->setMpBar(m_mpBar);
	m_player->setArmorBar(m_armorBar);
	m_map->addChild(m_player, 3, 200);
}

void TollgateScene::addWeapon()
{
	if (restore.num != 1)
	{
		m_player->setiTotalHp(restore.m_totalHp);
		m_player->setiNowHp(restore.m_nowHp);
		m_player->setiTotalArmor(restore.m_totalArmor);
		m_player->setiNowArmor(restore.m_nowArmor);
		m_player->setiTotalMp(restore.m_totalMp);
		m_player->setiNowMp(restore.m_nowMp);

		m_player->setIsUpgrate(restore.m_isUpgrate);
		m_player->setWeaponList(restore.weapons);
		m_player->setNumTotalWeapon(restore.m_numTotalWeapon);
		m_player->setNumWeapon(restore.m_numWeapon);
		m_player->setNumHasWeapon(restore.m_numHasWeapon);
		m_player->setLongRange(0);
		m_player->setLongRanges(restore.m_longRanges);
		m_player->determineWhichWeapon();

		return;
	}
	std::string str = "Pistol";
	m_player->setWeapon(str);
	m_player->determineWhichWeapon();
	/*str = "Fist_of_Heaven";
	m_player->setWeapon(str);
	m_player->determineWhichWeapon();
	str = "GoldenSword!";
	m_player->setWeapon(str);
	m_player->determineWhichWeapon();*/
	str = "StoneSword";
	m_player->setWeapon(str);
	m_player->determineWhichWeapon();
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
	playerController->setIsRanger(typeid(*m_player) == typeid(Ranger));
	playerController->setStandAnimate(animate);

}

void TollgateScene::loadEditBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	m_editBox = EditBox::create(Size(400, 50), "editBox.png");
	m_editBox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 600));
	m_editBox->setFontColor(Color3B::WHITE);
	m_editBox->setVisible(false);
	m_editBox->setEnabled(false);
	this->addChild(m_editBox);

	m_flowWord = FlowWord::create();
	m_flowWord->setPosition(Vec2(250, 200));
	this->addChild(m_flowWord);

	this->schedule(schedule_selector(TollgateScene::compare), 0.1f);
}

bool TollgateScene::init()
{
	if (!Layer::init())
		return false;
	loadMap();
	addPlayer();
	addWeapon();
	loadController();
	loadEditBox();
	loadMonsters();
	loadEditBox();
	return true;
}


void TollgateScene::onEnter()
{
	Layer::onEnter();
	this->scheduleUpdate();
	loadUI();
	loadListeners();
}

void TollgateScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	if (GameData::getBgmNum() == 1)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/advBgm.mp3", true);
		GameData::setBgmNum(ADVMAP);
	}
}

void TollgateScene::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_keyboard_listener);
	this->unscheduleUpdate();
	this->removeChildByTag(0);
}

void TollgateScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}
void TollgateScene::cleanup()
{
	Layer::cleanup();
}

void TollgateScene::loadUI()
{
	UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("INGAME_1.ExportJson");
	this->addChild(UI, 0, 0);
	m_cdBar = (LoadingBar*)Helper::seekWidgetByName(UI, "ability_loading_bar");
	m_hpBar = (LoadingBar*)Helper::seekWidgetByName(UI, "HP_bar");
	m_mpBar = (LoadingBar*)Helper::seekWidgetByName(UI, "magic_bar");
	m_armorBar = (LoadingBar*)Helper::seekWidgetByName(UI, "armor_bar");
	m_hp = (Text*)Helper::seekWidgetByName(UI, "HP_label");
	m_armor = (Text*)Helper::seekWidgetByName(UI, "armor_label");
	m_mp = (Text*)Helper::seekWidgetByName(UI, "magic_label");
	m_coin = (Text*)Helper::seekWidgetByName(UI, "coin_num");
	m_mp_cost = (Text*)Helper::seekWidgetByName(UI, "weapon_mp_label");
	m_weapon_image = (ImageView*)Helper::seekWidgetByName(UI, "weapon_image");
	m_weapon_button = (Button*)Helper::seekWidgetByName(UI, "weapon_button");
	m_weapon_button->addTouchEventListener(this, toucheventselector(TollgateScene::switchWeapon));
	m_boss_name = (Text*)Helper::seekWidgetByName(UI, "boss_name");
	m_boss_hp_bg = (LoadingBar*)Helper::seekWidgetByName(UI, "boss_hp_bg");
	m_boss_hp = (LoadingBar*)Helper::seekWidgetByName(UI, "boss_hp");
	auto pause_button = (Button*)Helper::seekWidgetByName(UI, "pause_button");
	pause_button->addTouchEventListener(this, toucheventselector(TollgateScene::pauseEvent));
}

void TollgateScene::pauseEvent(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		this->unscheduleUpdate();
		Size visible_size = Director::getInstance()->getVisibleSize();
		CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
		background->begin();
		this->visit();
		background->end();
		Director::getInstance()->pushScene(PauseScene::createScene(background, m_player->whichPlayer()));
		break;
	}
}

void TollgateScene::switchWeapon(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		m_player->changeWeapon();
		break;
	}
}

void TollgateScene::loadMonstersInNewRoom()
{
	auto roomCoord = m_monsterMgr->getCurRoom();
	m_monsterMgr->setRoomVisited(roomCoord);
	auto midPoint = GameData::getCoord()[static_cast<int>(5 * roomCoord.x + roomCoord.y)];
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10, -10)) * 32;
	m_monsterMgr->setPosition(LUPoint);

	
	if (!m_monsterMgr->getInited() || !m_monsterMgr->getMonster().size())
	{
		m_monsterMgr->createMonsters();
		m_monsterMgr->createMonsterPos();
		m_monsterMgr->createWoodWalls();
		m_monsterMgr->setInited();
		return;
	}
	m_monsterMgr->createOneMoreMons();//梯度
	m_monsterMgr->createOneMoreMons();
	m_monsterMgr->reviveAllMonsters();
}

 
void TollgateScene::loadMonsters()
{
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);
	//绑定房间
	m_monsterMgr = MonsterManager::create();
	//设置位置
	auto midPoint = GameData::getCoord()[static_cast<int>(5 * roomCoord.x + roomCoord.y)];
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10, -10)) * 32;
	m_monsterMgr->setPosition(LUPoint);

	//初始化工作
	m_monsterMgr->bindMap(m_map);
	m_monsterMgr->bindPlayer(static_cast<Entity*>(this->m_player));
	m_map->addChild(m_monsterMgr, 1);
}

void TollgateScene::loadBoss()
{
	auto roomCoord = m_monsterMgr->getCurRoom();
	m_monsterMgr->setRoomVisited(roomCoord);
	auto midPoint = GameData::getCoord()[static_cast<int>(5 * roomCoord.x + roomCoord.y)];
	midPoint.y = 186 - midPoint.y;
	auto LUPoint = (midPoint + ccp(-10, -10)) * 32;
	m_monsterMgr->setPosition(LUPoint);


	if (!m_monsterMgr->getInited())
	{
		m_monsterMgr->createBoss();
		m_monsterMgr->createWoodWalls();
		m_monsterMgr->setInited();
		return;
	}
	m_monsterMgr->createBoss();
	m_monsterMgr->createWoodWalls();
	m_boss_name->setVisible(true);
	//m_boss_hp_bg->setVisible(true);
	m_boss_hp->setVisible(true);
	//m_monsterMgr->reviveAllMonsters();
	
}

void TollgateScene::loadListeners()
{
	m_keyboard_listener = EventListenerKeyboard::create();
	m_keyboard_listener->onKeyPressed = [](EventKeyboard::KeyCode key, Event* event)
	{
		return true;
	};
	m_keyboard_listener->onKeyReleased = [=](EventKeyboard::KeyCode key, Event* event)
	{
		bool hasWeapon = false;
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_E:
			if (ccpDistance(m_player->getPosition(), m_map->getChest()->getPosition()) < 20.0f && m_map->getChest()->isVisible())
			{
				m_map->getChest()->setVisible(false);
				m_map->getChest()->setWeapon(rand() % 4 + 1);
				std::string str = m_map->getChest()->getWeapon()->getWeaponName();
				m_player->setWeapon(str);
				m_player->determineWhichWeapon();
			}
			else if (ccpDistance(m_player->getPosition(), m_map->getStatue()->getPosition()) < 20.0f)
			{
				if (m_map->getStatue()->getInteractionNum() == 1)//第一次互动
				{
					m_map->getStatue()->setInteractionNum(2);
					m_map->getStatue()->showFlowWordFirstMeet();
				}
				else
				{
					if (GameData::getCoinNum() >= m_map->getStatue()->getPrice())
					{
						GameData::setCoinNum(GameData::getCoinNum() - 15);
						m_map->getStatue()->showFlowWordEnoughMoney();
						//player获得buff加成
						m_player->getBuff(rand() % 3);
					}
					else
					{
						m_map->getStatue()->showFlowWordLackMoney();
					}
					m_map->getStatue()->setInteractionNum(1);
				}
			}
			else if (ccpDistance(m_player->getPosition(), m_map->getShop()->getPosition()) < 20.0f)
			{
				if (m_map->getShop()->getInteractionNum() == 1)//第一次互动
				{
					m_map->getShop()->setInteractionNum(2);
					m_map->getShop()->showFlowWordFirstMeet();
				}
				else
				{
					if (GameData::getCoinNum() >= m_map->getShop()->getPrice())
					{
						GameData::setCoinNum(GameData::getCoinNum() - 20);
						m_map->getShop()->setWeapon(rand() % 4 + 1);
						std::string str = m_map->getShop()->getWeapon()->getWeaponName();
						m_player->setWeapon(str);
						m_player->determineWhichWeapon();
						m_map->getShop()->showFlowWordEnoughMoney();
					}
					else
					{
						m_map->getShop()->showFlowWordLackMoney();
					}
					m_map->getShop()->setInteractionNum(1);
				}
			}
			if (ccpDistance(m_player->getPosition(), m_map->getPortal()->getPosition()) < 20.0f && m_map->getPortal()->isVisible())
			{
				this->unscheduleUpdate();
				if (GameData::getLevel() != 2)//传送到下一关
				{
					GameData::setLastRoomCoord(Vec2(2, 2));
					GameData::setLevel(GameData::getLevel() + 1);
					if (restore.num == 1)
					{
						restore.m_player = m_player;
						restore.weapons = m_player->getWeaponList();
						restore.m_totalHp = m_player->getiTotalHp();
						restore.m_nowHp = m_player->getiNowHp();
						restore.m_totalArmor = m_player->getiTotalArmor();
						restore.m_nowArmor = m_player->getiNowArmor();
						restore.m_totalMp = m_player->getiTotalMp();
						restore.m_nowMp = m_player->getiNowMp();

						restore.m_isUpgrate = m_player->getIsUpgrate();
						restore.weapons = m_player->getWeaponList();
						restore.m_numWeapon = m_player->getNumWeapon();
						restore.m_numHasWeapon = m_player->getNumHasWeapon();
						restore.m_numTotalWeapon = m_player->getNumTotalWeapon();
						restore.m_longRange = m_player->getLongRange();
					//	restore.m_longRanges = m_player->getLongRanges();
						restore.num++;
					}
					auto scene = TollgateScene::createScene();
					Director::getInstance()->replaceScene(scene);
				}
				else//结束冒险
				{
					GameData::setLastRoomCoord(Vec2(2, 2));
					this->unscheduleUpdate();
					Size visible_size = Director::getInstance()->getVisibleSize();
					CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
					background->begin();
					this->visit();
					background->end();
					restore.num = 1;
					Director::getInstance()->pushScene(FinishScene::createScene(background, m_player->whichPlayer()));
				}
			}
			for (auto redMedicine : m_map->getRedMedicineList())
			{
				if (redMedicine->isUsed())
				{
					continue;
				}
				if (ccpDistance(m_player->getPosition(), redMedicine->getPosition()) < 20.0f && redMedicine->isVisible())
				{
					m_player->setiNowHp(m_player->getiNowHp() + redMedicine->getRedValue());
					redMedicine->disappear();
				}
			}
			for (auto blueMedicine : m_map->getBlueMedicineList())
			{
				if (blueMedicine->isUsed())
				{
					continue;
				}
				if (ccpDistance(m_player->getPosition(), blueMedicine->getPosition()) < 20.0f && blueMedicine->isVisible())
				{
					m_player->setiNowMp(m_player->getiNowMp() + blueMedicine->getBlueMedicineValue());
					blueMedicine->disappear();
				}
			}
			for (auto longRange : m_map->getLongRangeList())
			{
				if (longRange->isUsed())
				{
					continue;
				}
				if (ccpDistance(m_player->getPosition(), longRange->getPosition()) < 40.0f && longRange->isVisible())
				{
					std::string str = longRange->getWeaponName();
					bool isUpgrate = longRange->getIsUpgarte();
					m_player->setWeapon(str, isUpgrate);
					m_player->determineWhichWeapon();
					longRange->disappear();
					hasWeapon = true;
					break;
				}
			}
			if (hasWeapon == false)
			{
				for (auto closeWeapon : m_map->getCloseWeaponList())
				{
					if (closeWeapon->isUsed())
					{
						continue;
					}
					if (ccpDistance(m_player->getPosition(), closeWeapon->getPosition()) < 40.0f && closeWeapon->isVisible())
					{
						std::string str = closeWeapon->getWeaponName();
						bool isUpgrate = closeWeapon->getIsUpgarte();
						m_player->setWeapon(str, isUpgrate);
						m_player->determineWhichWeapon();
						closeWeapon->disappear();
						break;
					}
				}
			}
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
			if (!m_editBox->isVisible())
			{
				m_editBox->setVisible(true);
				m_editBox->setEnabled(true);
				this->schedule(schedule_selector(TollgateScene::compare), 0.1f);
			}
			else
			{
				m_editBox->setText("");
				m_editBox->setVisible(false);
				m_editBox->setEnabled(false);
				this->unschedule(schedule_selector(TollgateScene::compare));
			}
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			this->unscheduleUpdate();
			Size visible_size = Director::getInstance()->getVisibleSize();
			CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
			background->begin();
			this->visit();
			background->end();
			Director::getInstance()->pushScene(PauseScene::createScene(background, m_player->whichPlayer()));
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_keyboard_listener, this);
}

void TollgateScene::updateMiniMap(TMXTiledMap* miniMap)
{

	auto miniMapLayer = miniMap->getLayer("miniMapLayer");
	auto playerPos = m_player->getPosition();
	auto roomCoord = m_map->roomCoordFromPosition(playerPos);

	if (roomCoord == Vec2(-1, -1))
	{
		return;
	}

	miniMapLayer->setTileGID(2, 2 * GameData::getLastRoomCoord());//浅灰
	miniMapLayer->setTileGID(1, 2 * Vec2(roomCoord.y, roomCoord.x));//深灰

	if (GameData::getLastRoomCoord() != Vec2(roomCoord.y, roomCoord.x))
	{
		if (GameData::getLastRoomCoord().x == roomCoord.y)//上下相连
		{
			miniMapLayer->setTileGID(4, GameData::getLastRoomCoord() + Vec2(roomCoord.y, roomCoord.x));
		}
		else//左右相连
		{
			miniMapLayer->setTileGID(3, GameData::getLastRoomCoord() + Vec2(roomCoord.y, roomCoord.x));
		}
	}
	GameData::setLastRoomCoord(Vec2(roomCoord.y, roomCoord.x));
}

void TollgateScene::compare(float dt)
{
	if (strcmp(m_editBox->getText(), "greedy") == 0)
	{
		GameData::setCoinNum(GameData::getCoinNum() + 100);
		CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
		auto str = pDictionary->valueForKey("GreedyCheat")->getCString();
		m_flowWord->showShopWord(str);
		this->unschedule(schedule_selector(TollgateScene::compare));
	}
	if (strcmp(m_editBox->getText(), "slaughter") == 0)
	{
		m_monsterMgr->killMonsters();
		CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
		auto str = pDictionary->valueForKey("SlaughterCheat")->getCString();
		m_flowWord->showShopWord(str);
		this->unschedule(schedule_selector(TollgateScene::compare));
	}
	if (strcmp(m_editBox->getText(), "hatewood") == 0)
	{
		m_monsterMgr->killWoodWall();
		CCDictionary* pDictionary = (CCDictionary*)CCDictionary::createWithContentsOfFile("ChineseCharacters.plist");
		auto str = pDictionary->valueForKey("WoodWallCheat")->getCString();
		m_flowWord->showShopWord(str);
		this->unschedule(schedule_selector(TollgateScene::compare));
	}
	if (strcmp(m_editBox->getText(), "magic") == 0)
	{
		m_player->setiNowMp(m_player->getiTotalMp());
		m_flowWord->showShopWord("无尽的魔力！");
		this->unschedule(schedule_selector(TollgateScene::compare));
	}
	if (strcmp(m_editBox->getText(), "rcwtql") == 0)
	{
		m_player->setInvincible(30.0f);
		this->unschedule(schedule_selector(TollgateScene::compare));
	}
	if (strcmp(m_editBox->getText(), "power") == 0)
	{
		m_player->setDamageBonus(10, 15.0f);
		m_flowWord->showShopWord("力量！！");
		this->unschedule(schedule_selector(TollgateScene::compare));
	}
}

int i = 0;

void TollgateScene::update(float dt)
{
	auto playerPos = m_player->getPosition();
	auto barrier = m_map->getCollidable();
	auto map = m_map->getMap();
	auto miniMap = m_map->getMiniMap();
	auto wall = m_map->getWall();
	auto roadPairs = m_map->getRoadPairs();
	updateMiniMap(miniMap);

	auto roomCoord = m_map->roomCoordFromPosition(playerPos);
	auto roomNum = roomCoord.x * 5 + roomCoord.y;
	
	(m_cdBar)->setPercent(m_player->getiNowCD() /
		static_cast<float>(m_player->getiTotalCD()) * 100);
	(m_armorBar)->setPercent(m_player->getiNowArmor() /
		static_cast<float>(m_player->getiTotalArmor()) * 100);
	(m_hpBar)->setPercent(m_player->getiNowHp() /
		static_cast<float>(m_player->getiTotalHp()) * 100);
	(m_mpBar)->setPercent(m_player->getiNowMp() /
		static_cast<float>(m_player->getiTotalMp()) * 100);
	m_weapon_image->loadTexture(m_player->getWeaponFileName());
	m_mp_cost->setText(std::to_string(m_player->getWeaponPowerCost()));
	if (!m_map->isBossRoom(roomCoord))
	
	{
		m_boss_name->setVisible(false);
		m_boss_hp_bg->setVisible(false);
		m_boss_hp->setVisible(false);
	}
	else
	{
		m_boss_name->setVisible(true);
		m_boss_hp_bg->setVisible(true);
		m_boss_hp->setVisible(true);
		m_boss_hp->setPercent(m_monsterMgr->getMonsterHpRate());
	}

	m_hp->setText(std::to_string(m_player->getiNowHp()) + "/" + std::to_string(m_player->getiTotalHp()));
	m_armor->setText(std::to_string(m_player->getiNowArmor()) + "/" + std::to_string(m_player->getiTotalArmor()));
	m_mp->setText(std::to_string(m_player->getiNowMp()) + "/" + std::to_string(m_player->getiTotalMp()));
	m_coin->setText(std::to_string(GameData::getCoinNum()));


	if ((m_map->isMonsterRoom(roomCoord) || m_map->isBossRoom(roomCoord))	//首先它得是个怪物房间
		&& !m_monsterMgr->isRoomVisited(roomCoord))//其次它没有被到访过
	{
		m_monsterMgr->setCurRoom(roomCoord);
		if (m_map->isBossRoom(roomCoord))//如果是boss房
		{
			m_map->getPortal()->setVisible(false);
			loadBoss();
		}
		else
		{
			loadMonstersInNewRoom();
		}
	}
	Vec2 dir[4] = { {0,1},{0,-1},{1,0},{-1,0} };

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
	if (m_monsterMgr->isGameOver())
	{
		for (auto elem : dirVec)
		{
			AdventureMapLayer::switchGate(wall, barrier, roomNum, elem, false);
		}
		m_map->getPortal()->setVisible(true);
		miniMap->setVisible(true);
	}

	//碰撞检测
	auto player_bullet = m_player->getBullet();
	auto monsters_bullet = m_monsterMgr->getMonsterBullets();
	auto monsters = m_monsterMgr->getMonster();
	auto woodWalls = m_monsterMgr->getWoodWall();
	for (auto woodWall : woodWalls)
	{
		monsters.push_back(woodWall);
	}
	//player bullet
	for (auto bullet : player_bullet)
	{
		if (bullet->isUsed())
		{
			continue;
		}
		cocos2d::Point bullet_pos = bullet->getPosition();
		if (m_map->isBarrier(bullet_pos))
		{
			if (typeid(*bullet) == typeid(ExplosiveBullet))
			{
				auto explosive_bullet = dynamic_cast<ExplosiveBullet*>(bullet);
				if (!explosive_bullet->isUsed() && !explosive_bullet->isExplode())
				{
					explosive_bullet->explode();
				}
				for (auto unlucky_monster : monsters)
				{
					if (unlucky_monster->isAlive())
					{
						cocos2d::Point explosive_origin_point = m_map->convertToWorldSpace(explosive_bullet->getPosition());
						if (unlucky_monster->getBoundingBox().intersectsCircle(explosive_origin_point, explosive_bullet->getExplosionRange()))
						{
							unlucky_monster->hit(explosive_bullet->getExplosionDamage() * m_player->getDamageBonus(), bullet->getDegree(), 0);
						}
					}
				}

			}
			else bullet->setIsUsed(true);
		}
		for (auto monster : monsters)
		{
			
			if (monster->isAlive())
			{
				if (bullet->isCollideWith(monster))
				{

					int damage = bullet->getDamage();
					if (CCRANDOM_0_1() < bullet->getCritRate())
					{
						damage *= 2;
						monster->hit(damage * m_player->getDamageBonus(), bullet->getDegree(), 1);
					}
					else
						monster->hit(damage * m_player->getDamageBonus(), bullet->getDegree(), 0);


					if (typeid(*bullet) == typeid(ExplosiveBullet))
					{
						auto explosive_bullet = dynamic_cast<ExplosiveBullet*>(bullet);
						if (!explosive_bullet->isUsed() && !explosive_bullet->isExplode())
						{
							explosive_bullet->explode();
						}
						for (auto unlucky_monster : monsters)
						{
							if (unlucky_monster->isAlive())
							{
								cocos2d::Point explosive_origin_point = m_map->convertToWorldSpace(explosive_bullet->getPosition());
								if (unlucky_monster->getBoundingBox().intersectsCircle(explosive_origin_point, explosive_bullet->getExplosionRange()))
								{
									unlucky_monster->hit(explosive_bullet->getExplosionDamage() * m_player->getDamageBonus(), explosive_bullet->getDegree(), 1);
								}
							}
						}
					}
					else bullet->setIsUsed(true);
				}
			}
		}
	}

	if (m_player->isAttackingWithCloseWeapon())
	{
		auto weapon = m_player->getCloseWeapon();
		if (!weapon->isHit())
		{
			for (auto monster : monsters)
			{
				if (weapon->isCollideWith(monster))
				{
					int damage = weapon->getDamage();
					if (CCRANDOM_0_1() < weapon->getCritRate())
					{
						damage *= 2;
						monster->hit(damage * m_player->getDamageBonus(), 0.0f, 1);
						if (typeid(*m_player) == typeid(Knight) && dynamic_cast<Knight*>(m_player)->getIsInSkill())
						{
							monster->hit(damage * m_player->getDamageBonus(), 0.0f, 1);
						}
					}
					else
					{
						monster->hit(damage * m_player->getDamageBonus(), 0.0f, 0);
						if (typeid(*m_player) == typeid(Knight) && dynamic_cast<Knight*>(m_player)->getIsInSkill())
						{
							monster->hit(damage * m_player->getDamageBonus(), 0.0f, 0);
						}
					}
				}
			}
			weapon->setIsHit(true);
		}
	}

	//monster bullet
	for (auto bullet : monsters_bullet)
	{
		if (bullet->isUsed())
		{
			continue;
		}
		cocos2d::Point bullet_pos = bullet->getPosition();
		if (m_map->isBarrier(bullet_pos))
		{
			bullet->setIsUsed(true);
		}
		if (bullet->isCollideWith(m_player))
		{
			if (!m_player->isInvincible())
			{
				m_player->hit(bullet->getDamage());
			}
			bullet->setIsUsed(true);
		}
		for (auto woodwall : woodWalls)
		{
			if (bullet->isCollideWith(woodwall))
			{
				woodwall->hit(bullet->getDamage());
			}
		}
	}

	for (auto monster : monsters)
	{
		Weapon* weapon = monster->getMonsterWeapon();
		if (weapon)
		{
			if (weapon->isCloseWeapon())
			{
				auto close_weapon = dynamic_cast<CloseWeapon*>(weapon);
				if (!close_weapon->isHit())
				{
					if (close_weapon->isCollideWith(m_player))
					{
						if (!m_player->isInvincible())
						{
							m_player->hit(close_weapon->getDamage());
						}
						close_weapon->setIsHit(true);
					}
				}
			}
		}
	}
	//小金币和小蓝的自动拾取
	for (auto coin : m_map->getCoinList())
	{
		if (coin->isUsed())
		{
			continue;
		}
		if (ccpDistance(coin->getPosition(), m_player->getPosition()) < 100.0f && coin->isVisible())
		{
			auto moveBy = MoveBy::create(1.0f / 60.0f, (m_player->getPosition() - coin->getPosition()) / 5.0f);
			coin->runAction(moveBy);
			if (ccpDistance(coin->getPosition(), m_player->getPosition()) < 20.0f)
			{
				coin->disappear();
				GameData::setCoinNum(GameData::getCoinNum() + coin->getPrice());
			}
		}
	}
	for (auto blue : m_map->getBlueList())
	{
		if (blue->isUsed())
		{
			continue;
		}
		if (ccpDistance(blue->getPosition(), m_player->getPosition()) < 100.0f && blue->isVisible())
		{
			auto moveBy = MoveBy::create(1.0f / 60.0f, (m_player->getPosition() - blue->getPosition()) / 5.0f);
			blue->runAction(moveBy);
			if (ccpDistance(blue->getPosition(), m_player->getPosition()) < 20.0f)
			{
				m_player->setiNowMp(m_player->getiNowMp() + blue->getBlueValue());
				blue->disappear();
			}
		}
	}

	if (m_player->getIsDeath())
	{
		this->unscheduleUpdate();
		Size visible_size = Director::getInstance()->getVisibleSize();
		CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
		background->begin();
		this->visit();
		background->end();
		Director::getInstance()->pushScene(DeathScene::createScene(background, m_player));
	}
}
