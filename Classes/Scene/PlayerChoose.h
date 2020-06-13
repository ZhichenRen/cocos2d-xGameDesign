#ifndef __PlayerChoose_H__
#define __PlayerChoose_H__

#include "cocos2d.h"
using namespace cocos2d;

class PlayerChoose:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PlayerChoose);
	void setPlayer();
	void back();
protected:
	std::string* m_player_name;
	void loadUI();
};

#endif
