#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"


class HomeMenuLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuItemStartCallback(cocos2d::Ref* pSender);
	void menuItemSettingCallback(cocos2d::Ref* pSender);
	void menuItemCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(HomeMenuLayer);
};


#endif // !__HOME_SCENE_H__