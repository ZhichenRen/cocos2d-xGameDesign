#ifndef __Slime_H__
#define __Slime_H__
#include "cocos2d.h"
#include "Monster\Monster.h"

class Slime : public Monster {
public:
	virtual bool init();
	CREATE_FUNC(Slime);
	virtual void resetPropoties();
private:
	
};
#endif // !__Slime_H__
