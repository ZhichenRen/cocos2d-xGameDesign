#include "TollgateScene.h"
#include "Monster\MonsterManager.h"
Scene* TollgateScene::createScene() 
{
    auto scene = Scene::create();
    auto layer = TollgateScene::create();
    scene->addChild(layer);

    return scene;
}

bool TollgateScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MonsterManager* monsterMgr = MonsterManager::create();
    this->addChild(monsterMgr, 4);
    return true;
}