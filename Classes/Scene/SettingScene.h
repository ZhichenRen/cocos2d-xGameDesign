#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SettingLayer :public cocos2d::Layer
{
	//bool m_isEffect;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	//void sliderCallback(cocos2d::Ref* pSender,cocos2d::ui::Slider::EventType type);

	//void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(SettingLayer);
};


#endif // !__SETTING_SCENE_H__

