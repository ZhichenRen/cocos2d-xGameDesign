#include "SafeMapScene.h"
#include "AdventureMapScene.h"

USING_NS_CC;

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

	this->scheduleUpdate();

	m_tileMap = TMXTiledMap::create("map/SafeMap.tmx");//创建地图
	this->addChild(m_tileMap);

    m_collidable = m_tileMap->getLayer("barrier");//获取判断碰撞的障碍层

	TMXObjectGroup* group = m_tileMap->getObjectGroup("objects");//获取对象层
	ValueMap spawnPoint = group->getObject("hero");//根据hero对象的位置放置精灵

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	m_player = Sprite::create("map/hero.png");
	m_player->setPosition(Vec2(x, y));
	this->addChild(m_player);//游戏人物

	return true;
}

void SafeMapLayer::onEnter()
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

void SafeMapLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void SafeMapLayer::onExit()
{
	Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void SafeMapLayer::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void SafeMapLayer::cleanup()
{
	Layer::cleanup();
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
    }
    if (m_keyMap[moveRight])
    {
        offset.x = 4;
    }

    auto playerPos = m_player->getPosition();
    this->setPlayerPosition(playerPos + offset, offset.x, offset.y);

    Vec2 a = { 512-32,768 };
    Vec2 b = { 512+32,768-32 };
    if (m_player->getPosition().x >= a.x && m_player->getPosition().x <= b.x && 
        m_player->getPosition().y <= a.y && m_player->getPosition().y >= b.y)
    {
        auto scene = AdventureMapLayer::createScene();
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

    this->setPosition(offset);
}