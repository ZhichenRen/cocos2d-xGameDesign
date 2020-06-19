#ifndef __AboutAuthor_H__
#define __AboutAuthor_H__
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class AboutAuthor :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(AboutAuthor);
private:
	void loadUI();
	void back(Ref*, TouchEventType type);
};

#endif