#ifndef __DeathScene_H__
#define __DeathScene_H__
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class Player;
class DeathScene :public Layer
{
public:
	virtual bool init();
	static Scene* createScene(CCRenderTexture* background, Player* player);
	CREATE_FUNC(DeathScene);
private:
	void loadUI();
	void backToHomeMenu(Ref*, TouchEventType type);
	void respawn(Ref*, TouchEventType type);
	void aboutAuthor(Ref*, TouchEventType type);
	void setPlayer(Player* player);
	Player* m_player;
};

#endif