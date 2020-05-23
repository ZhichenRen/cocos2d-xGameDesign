#ifndef __PauseScene_H__
#define __PauseScene_H__

#include "cocos2d.h"

using namespace cocos2d;

class PauseScene :public Layer
{
public:
	virtual bool init();
	static Scene* createScene(CCRenderTexture* background);
	CREATE_FUNC(PauseScene);
};

#endif
