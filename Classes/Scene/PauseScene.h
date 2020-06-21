#ifndef __PauseScene_H__
#define __PauseScene_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class PauseScene :public Layer
{
public:
	virtual bool init();
	static Scene* createScene(CCRenderTexture* background, int player);
	CREATE_FUNC(PauseScene);
	void setPlayer(int player);
private:
	void loadUI();
	void backToHomeMenu(Ref*, TouchEventType type);
	void resume(Ref*, TouchEventType type);
	void goToSettingMenu(Ref*, TouchEventType type);
	int m_player;
};

#endif