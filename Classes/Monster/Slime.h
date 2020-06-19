#ifndef __Slime_H__
#define __Slime_H__
#include "cocos2d.h"
#include "Monster\Monster.h"

class Slime : public Monster {
public:
	virtual bool init();
	virtual void resetPropoties();
	CREATE_FUNC(Slime);
	//virtual void resetPropoties();
private:
	static const int m_initHp = 10;
};
#endif // !__Slime_H__
