#include "Scene\AdventureMapScene.h"
#include "SimpleAudioEngine.h"
#include "Entity\Coin\Coin.h"
//#include "Entity\Weapons\RPG.h"
//#include "Entity\Weapons\Shotgun.h"
#include "Entity\Weapons\CandyGun.h"
#include "Monster\MonsterManager.h"

USING_NS_CC;

Scene* AdventureMapLayer::createScene()
{
    auto scene = Scene::create();

    auto layer = AdventureMapLayer::create();
    
    

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool AdventureMapLayer::init()
{
    //1. super init first
    if (!Layer::init())
    {
        return false;
    }

    createRandomMap();
    this->addChild(m_tileMap, 0, 100);//游戏地图 tag为100

    TMXObjectGroup* group = m_tileMap->getObjectGroup("objects");//获取对象层
    ValueMap spawnPoint = group->getObject("hero");//根据hero对象的位置放置精灵
    
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();
    
    m_player = Sprite::create("hero.png");
    m_player->setPosition(Vec2(x,y));
    
	auto gun = RPG::create();
	gun->bindMap(this);
	gun->setPosition(1, 1);
	m_player->addChild(gun);

    auto monsterMgr = MonsterManager::create();
    monsterMgr->bindMap(this);
    monsterMgr->bindPlayer(m_player);
    monsterMgr->setPosition(x - 9*32, y - 9*32);
    this->addChild(monsterMgr,1);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = [gun](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		gun->attack(pos);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->addChild(m_player, 2, 200);//游戏人物 tag为200

    setViewpointCenter(m_player->getPosition());

	auto coin = Coin::create();
	coin->setPosition(convertToNodeSpace(convertToWorldSpace(m_player->getPosition())));
	this->addChild(coin, 2);
    return true;
}

void AdventureMapLayer::onEnter()
{
    Layer::onEnter();

    auto listener = EventListenerKeyboard::create();//创建监听事件

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
    {
        m_keyMap[keycode] = true;
    };
    
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event)
    {
        m_keyMap[keycode] = false;
    };

    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void AdventureMapLayer::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void AdventureMapLayer::update(float dt)
{
    auto moveUp = EventKeyboard::KeyCode::KEY_W;
    auto moveDown = EventKeyboard::KeyCode::KEY_S;
    auto moveLeft = EventKeyboard::KeyCode::KEY_A;
    auto moveRight = EventKeyboard::KeyCode::KEY_D;

    Vec2 offset(0, 0);//偏移量
    
    float dx = 0, dy = 0;

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
    }
    if (m_keyMap[moveRight])
    {
        offset.x = 4;
    }

    auto playerPos = m_player->getPosition();
    this->setPlayerPosition(playerPos + offset,offset.x,offset.y);

    //auto moveBy = MoveBy::create(0.001f, m_player->getPosition()-playerPos);
    //m_player->runAction(moveBy);
}



void AdventureMapLayer::setPlayerPosition(Vec2 position,int dx,int dy)
{
    Vec2 tileCoord = this->tileCoordFromPosition(position);//像素坐标转换为瓦片坐标

    int tileGid = m_collidable->getTileGIDAt(tileCoord);//获得瓦片的GID

    if (tileGid != 0)//瓦片是否存在（不存在时tileGid==0）
    {
        
        auto prop = m_tileMap->getPropertiesForGID(tileGid);
        auto valueMap = prop.asValueMap();
        bool collision = valueMap["Collidable"].asBool();
        if (collision == true)//碰撞检测
        {
            m_player->setPosition(position-Vec2(dx,dy));//回弹，否则会卡墙里
            return;
        }
    }
    m_player->setPosition(position);//移动精灵

    this->setViewpointCenter(m_player->getPosition());//滚动地图
}
    return true;
}

//像素坐标转换为瓦片坐标
cocos2d::Vec2 AdventureMapLayer::tileCoordFromPosition(cocos2d::Vec2 pos)
{
    int x = pos.x / m_tileMap->getTileSize().width;
    int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - pos.y) / m_tileMap->getTileSize().height;

    return Vec2(x, y);
}


cocos2d::Point AdventureMapLayer::convertToMapSpace(const cocos2d::Point& point)
{
    return convertToNodeSpace(point);
}

std::map<Vec2, bool> AdventureMapLayer::getBarrierMap()
{
    return this->m_barrierMap;
}

bool AdventureMapLayer::isBarrier(Vec2 position)
{
    Vec2 tileCoord = this->tileCoordFromPosition(position);//像素坐标转换为瓦片坐标

    int tileGid = m_collidable->getTileGIDAt(tileCoord);//获得瓦片的GID

    if (tileGid != 0)//瓦片是否存在（不存在时tileGid==0）
    {
        auto prop = m_tileMap->getPropertiesForGID(tileGid);
        auto valueMap = prop.asValueMap();
        return valueMap["Collidable"].asBool();
    }
    return false;
}
