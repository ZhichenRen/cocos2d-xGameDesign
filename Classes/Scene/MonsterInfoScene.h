#ifndef __MONSTER_INFO_SCENE_H__
#define __MONSTER_INFO_SCENE_H__
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class MonsterInfoScene :public Layer
{
public:
	virtual bool init();
	static Scene* createScene(CCRenderTexture* background);
	CREATE_FUNC(MonsterInfoScene);
	void back(Ref*, TouchEventType type);
private:
	void loadUI();
	Widget* m_ui = NULL;
	Button* m_back_button = NULL;
};

#endif