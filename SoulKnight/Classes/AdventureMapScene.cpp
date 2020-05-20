#include "AdventureMapScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _tileMap = TMXTiledMap::create("AdventureMapLevel1.tmx");//创建地图
    addChild(_tileMap, 0, 100);//游戏地图 tag为100

    TMXObjectGroup* group = _tileMap->getObjectGroup("objects");//获取对象层
    ValueMap spawnPoint = group->getObject("hero");//根据hero对象的位置放置精灵
    
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();

    _player = Sprite::create("hero.png");
    _player->setPosition(Vec2(x,y));
    log("starting position:(%d,%d)", x, y);
    addChild(_player, 2, 200);//游戏人物 tag为200

    setViewpointCenter(_player->getPosition());

    _collidable = _tileMap->getLayer("barrier");//获取判断碰撞的障碍层
    //_collidable->setVisible(false);

    return true;
}

void HelloWorld::onEnter()
{
    Layer::onEnter();

    auto listener = EventListenerKeyboard::create();//创建监听事件

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
    {
        _keyMap[keycode] = true;
    };
    
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event)
    {
        _keyMap[keycode] = false;
    };

    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void HelloWorld::update(float dt)
{
    auto moveUp = EventKeyboard::KeyCode::KEY_W;
    auto moveDown = EventKeyboard::KeyCode::KEY_S;
    auto moveLeft = EventKeyboard::KeyCode::KEY_A;
    auto moveRight = EventKeyboard::KeyCode::KEY_D;

    Vec2 offset(0, 0);//偏移量
    //每帧移动两个像素
    if (_keyMap[moveUp])
    {
        offset.y = 2;
    }
    if (_keyMap[moveDown])
    {
        offset.y = -2;
    }
    if (_keyMap[moveLeft])
    {
        offset.x = -2;
    }
    if (_keyMap[moveRight])
    {
        offset.x = 2;
    }

    auto playerPos = _player->getPosition();
    this->setPlayerPosition(playerPos + offset,offset.x,offset.y);

    auto moveBy = MoveBy::create(0.01f, _player->getPosition()-playerPos);
    _player->runAction(moveBy);
}

void HelloWorld::setPlayerPosition(Vec2 position,int dx,int dy)
{
    Vec2 tileCoord = this->tileCoordFromPosition(position);//像素坐标转换为瓦片坐标

    int tileGid = _collidable->getTileGIDAt(tileCoord);//获得瓦片的GID
 
    if (tileGid != 0)//瓦片是否存在（不存在时tileGid==0）
    {
        
        auto prop = _tileMap->getPropertiesForGID(tileGid);
        auto valueMap = prop.asValueMap();
        bool collision = valueMap["Collidable"].asBool();
        if (collision == true)//碰撞检测
        {
            _player->setPosition(position-Vec2(dx,dy));//回弹，否则会卡墙里
            return;
        }
    }
    _player->setPosition(position);//移动精灵

    this->setViewpointCenter(_player->getPosition());//滚动地图
}

//像素坐标转换为瓦片坐标
cocos2d::Vec2 HelloWorld::tileCoordFromPosition(cocos2d::Vec2 pos)
{
    int x = pos.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;

    return Vec2(x, y);
}

//将人物保持在屏幕中间
void HelloWorld::setViewpointCenter(cocos2d::Vec2 position)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //防止屏幕左边超出地图
    float x = MAX(position.x, visibleSize.width / 2);
    float y = MAX(position.y, visibleSize.height / 2);
    //防止屏幕右边超出地图
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getMapSize().width) - visibleSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getMapSize().height) - visibleSize.height / 2);

    Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);//屏幕的中点
    Vec2 pointB = Vec2(x, y);//目标点

    Vec2 offset = pointA - pointB;//偏移量

    this->setPosition(offset);
}
