#include "Scene\PauseScene.h"

bool PauseScene::init()
{
	log("INIT");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		log("Touch!");
		Director::getInstance()->popScene();
		return true;
	};
	listener->onTouchEnded = [](Touch* touch, Event* event)
	{
		Director::getInstance()->popScene();
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

Scene* PauseScene::createScene(CCRenderTexture* background)
{
	Scene* scene = Scene::create();
	Layer* layer = PauseScene::create();
	scene->addChild(layer, 1);
	
	Size visible_size = Director::getInstance()->getVisibleSize();
	Sprite* background_picture = Sprite::createWithTexture(background->getSprite()->getTexture());
	background_picture->setPosition(visible_size.width / 2, visible_size.height / 2);
	background_picture->setFlippedY(true);
	scene->addChild(background_picture, 0);

	Label* label = Label::create("Touch screen to continue", "Arial", 30);
	label->setPosition(visible_size.width / 2, visible_size.height / 2);
	scene->addChild(label, 1);

	log("LOG WORK");
	return scene;
}