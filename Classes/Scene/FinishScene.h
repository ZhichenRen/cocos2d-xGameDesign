#ifndef __FinishScene_H__
#define __FinishScene_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class FinishScene :public Layer
{
public:
	virtual bool init();
	static Scene* createScene(CCRenderTexture* background, int player);
	CREATE_FUNC(FinishScene);
private:
	void loadUI();
	void backToHomeMenu(Ref*, TouchEventType type);
	void aboutAuthor(Ref*, TouchEventType type);
	void setPlayer(int player);
	int m_player;
};

#endif
