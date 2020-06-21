#include "Scene/SafeMapScene.h"
#include "Scene/AdventureMapScene.h"
#include "Scene/TollgateScene.h"
#include "SimpleAudioEngine.h"
#include "extensions\cocos-ext.h"
#pragma execution_character_set("utf-8")

USING_NS_CC_EXT;
USING_NS_CC;
using namespace CocosDenshion;

int SafeMapLayer::m_choose_player = 1;

cocos2d::Scene* SafeMapLayer::createScene()
{
    auto scene = Scene::create();

    auto layer = SafeMapLayer::create();

    scene->addChild(layer);

    return scene;
}

bool SafeMapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    m_tileMap = TMXTiledMap::create("map/SafeMap.tmx");//创建地图
    this->addChild(m_tileMap);

    m_collidable = m_tileMap->getLayer("barrier");//获取判断碰撞的障碍层

    TMXObjectGroup* group = m_tileMap->getObjectGroup("objects");//获取对象层
    ValueMap spawnPointWeaponInfo = group->getObject("weaponInfo");
    ValueMap spawnPointMonsterInfo = group->getObject("monsterInfo");

    float x = spawnPointWeaponInfo["x"].asFloat();
    float y = spawnPointWeaponInfo["y"].asFloat();

    m_weaponInfo = Sprite::create("weaponInfo.png");
    m_weaponInfo->setPosition(Vec2(x, y));
    m_tileMap->addChild(m_weaponInfo);

    x = spawnPointMonsterInfo["x"].asFloat();
    y = spawnPointMonsterInfo["y"].asFloat();

    m_monsterInfo = Sprite::create("monsterInfo.png");
    m_monsterInfo->setPosition(Vec2(x, y));
    m_tileMap->addChild(m_monsterInfo);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    MenuItemImage* settingItem = MenuItemImage::create("menu/SettingNormal.png", "menu/SettingSelected.png", CC_CALLBACK_1(SafeMapLayer::menuItemSettingCallback, this));
    settingItem->setPosition(Vec2(origin.x + visibleSize.width - 100, origin.y + visibleSize.height - 50));

    Menu* menu1 = Menu::create(settingItem, nullptr);

    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 0, 10085);//设置菜单

    MenuItemFont* text = MenuItemFont::create("选择你的英雄");
    text->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 200));

    MenuItemImage* rangerItem = MenuItemImage::create("ranger_image.png", "ranger_image.png", CC_CALLBACK_1(SafeMapLayer::menuItemRangerCallback, this));
    rangerItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 300, origin.y + visibleSize.height / 2 - 200));

    MenuItemImage* priestItem = MenuItemImage::create("priest_image.jpg", "priest_image.jpg", CC_CALLBACK_1(SafeMapLayer::menuItemPriestCallback, this));
    priestItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 200));

    MenuItemImage* knightItem = MenuItemImage::create("knight_image.png", "knight_image.png", CC_CALLBACK_1(SafeMapLayer::menuItemKnightCallback, this));
    knightItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 300, origin.y + visibleSize.height / 2 - 200));

    Menu* menu2 = Menu::create(text, rangerItem, priestItem, knightItem, nullptr);

    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 0, 10086);//选人菜单

    return true;
}

void SafeMapLayer::onEnter()
{
    Layer::onEnter();

    m_listener = EventListenerKeyboard::create();//创建监听事件

    m_listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
    {
        m_keyMap[keycode] = true;
        if (keycode == EventKeyboard::KeyCode::KEY_E)
        {
            if (ccpDistance(m_player->getPosition(), m_weaponInfo->getPosition()) < 50.0f)//武器图鉴
            {
                m_keyMap[EventKeyboard::KeyCode::KEY_W] = false;
                m_keyMap[EventKeyboard::KeyCode::KEY_A] = false;
                m_keyMap[EventKeyboard::KeyCode::KEY_S] = false;
                m_keyMap[EventKeyboard::KeyCode::KEY_D] = false;
                Size visible_size = Director::getInstance()->getVisibleSize();
                CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
                background->begin();
                this->visit();
                background->end();
                Director::getInstance()->pushScene(WeaponInfoScene::createScene(background));
            }
            else if (ccpDistance(m_player->getPosition(), m_monsterInfo->getPosition()) < 50.0f)//怪物图鉴
            {
                m_keyMap[EventKeyboard::KeyCode::KEY_W] = false;
                m_keyMap[EventKeyboard::KeyCode::KEY_A] = false;
                m_keyMap[EventKeyboard::KeyCode::KEY_S] = false;
                m_keyMap[EventKeyboard::KeyCode::KEY_D] = false;
                Size visible_size = Director::getInstance()->getVisibleSize();
                CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
                background->begin();
                this->visit();
                background->end();
                Director::getInstance()->pushScene(MonsterInfoScene::createScene(background));
            }
        }
    };

    m_listener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event)
    {
        m_keyMap[keycode] = false;
    };

    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
}

void SafeMapLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    if (GameData::getBgmNum() == ADVMAP)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/safeBgm.mp3", true);
    }
}

void SafeMapLayer::onExit()
{
    Layer::onExit();
    this->unschedule(schedule_selector(SafeMapLayer::update));
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}

void SafeMapLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}

void SafeMapLayer::cleanup()
{
    Layer::cleanup();
}

void SafeMapLayer::setPlayer(int playerNum)
{
    TMXObjectGroup* group = m_tileMap->getObjectGroup("objects");//获取对象层
    ValueMap spawnPoint = group->getObject("hero");//根据hero对象的位置放置精灵

    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();
	auto animation = AnimationUtil::createWithFrameNameAndNumUsingPlist("Ranger/RangerWalk/", "RangerWalk", 4, 0.12, -1);
	auto animate = Animate::create(animation);
    switch (playerNum)
    {
    case 1:
        m_player = Sprite::create("Ranger/RangerIni.png");
        m_player->setPosition(Vec2(x, y));
        m_tileMap->addChild(m_player);//游戏人物
        this->removeChildByTag(10086);
		m_player->runAction(animate);
        this->scheduleUpdate();
        break;
    case 2:
        m_player = Sprite::create("Priest/PriestIni.PNG");
		m_player->setScale(0.5);
        m_player->setPosition(Vec2(x, y));
        m_tileMap->addChild(m_player);//游戏人物
        this->removeChildByTag(10086);
        this->scheduleUpdate();
        break;
    case 3:
        m_player = Sprite::create("Knight/KnightIni.png");
        m_player->setPosition(Vec2(x, y));
        m_tileMap->addChild(m_player);//游戏人物
        this->removeChildByTag(10086);
        this->scheduleUpdate();
    }
}

void SafeMapLayer::menuItemSettingCallback(cocos2d::Ref* pSender)
{
    Size visible_size = Director::getInstance()->getVisibleSize();
    CCRenderTexture* background = CCRenderTexture::create(visible_size.width, visible_size.height);
    background->begin();
    this->visit();
    background->end();
    Director::getInstance()->pushScene(PauseScene::createScene(background, m_choose_player));
}

void SafeMapLayer::menuItemRangerCallback(cocos2d::Ref* pSender)
{
    SafeMapLayer::m_choose_player = 1;
    auto layer = PlayerChoose::create();
    layer->bindMap(this);
    this->addChild(layer, 10000);
}

void SafeMapLayer::menuItemPriestCallback(cocos2d::Ref* pSender)
{
    SafeMapLayer::m_choose_player = 2;
    auto layer = PlayerChoose::create();
    layer->bindMap(this);
    PlayerInfomation priest = {
        3,
        5,
        200,
        "牧师",
        "恢复法阵",
        "使用恢复法阵\n恢复生命值",
        "priest_image.jpg",
        "priest_ability.jpg"
    };
    layer->setPlayerInformation(priest);
    this->addChild(layer, 10001);
}

void SafeMapLayer::menuItemKnightCallback(cocos2d::Ref* pSender)
{
    SafeMapLayer::m_choose_player = 3;
    auto layer = PlayerChoose::create();
    layer->bindMap(this);
    PlayerInfomation knight = {
        6,
        5,
        180,
        "骑士",
        "火力全开",
        "短时间内使用两把枪",
        "knight_image.png",
        "knight_ability.png"
    };
    layer->setPlayerInformation(knight);
    this->addChild(layer, 10002);
}

void SafeMapLayer::update(float dt)
{
    auto moveUp = EventKeyboard::KeyCode::KEY_W;
    auto moveDown = EventKeyboard::KeyCode::KEY_S;
    auto moveLeft = EventKeyboard::KeyCode::KEY_A;
    auto moveRight = EventKeyboard::KeyCode::KEY_D;

    Vec2 offset(0, 0);//偏移量
    //每帧移动两个像素
    if (m_keyMap[moveUp])
    {
        offset.y = 4;
    }
    if (m_keyMap[moveDown])
    {
        offset.y = -4;
    }
    if (m_keyMap[moveLeft])
    {
        offset.x = -4;
        m_player->runAction(FlipX::create(true));
    }
    if (m_keyMap[moveRight])
    {
        offset.x = 4;
        m_player->runAction(FlipX::create(false));
    }

    auto playerPos = m_player->getPosition();
    this->setPlayerPosition(playerPos + offset, offset.x, offset.y);

    Vec2 a = { 512 - 32,768 };
    Vec2 b = { 512 + 32,768 - 32 };
    if (m_player->getPosition().x >= a.x && m_player->getPosition().x <= b.x &&
        m_player->getPosition().y <= a.y && m_player->getPosition().y >= b.y)
    {
        auto scene = TollgateScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void SafeMapLayer::setPlayerPosition(Vec2 position, int dx, int dy)
{
    Vec2 tileCoord = this->tileCoordFromPosition(position);//像素坐标转换为瓦片坐标

    int tileGid = m_collidable->getTileGIDAt(tileCoord);//获得瓦片的GID

    if (tileGid != 0)//瓦片是否存在（不存在时tileGid==0）
    {

        auto prop = m_tileMap->getPropertiesForGID(tileGid);
        auto valueMap = prop.asValueMap();
        bool collision = valueMap["Collidable"].asBool();
        if (collision)//碰撞检测
        {
            m_player->setPosition(position - Vec2(dx, dy));//回弹，否则会卡墙里
            return;
        }
    }
    m_player->setPosition(position);//移动精灵

    this->setViewpointCenter(m_player->getPosition());//滚动地图
}

//像素坐标转换为瓦片坐标
cocos2d::Vec2 SafeMapLayer::tileCoordFromPosition(cocos2d::Vec2 pos)
{
    int x = pos.x / m_tileMap->getTileSize().width;
    int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - pos.y) / m_tileMap->getTileSize().height;

    return Vec2(x, y);
}

//将人物保持在屏幕中间
void SafeMapLayer::setViewpointCenter(cocos2d::Vec2 position)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 centerPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);//屏幕的中点

    Vec2 offset = centerPoint - position;//偏移量

    m_tileMap->setPosition(offset);
}