#ifndef __ChiefOfTribe_H__
#define __ChiefOfTribe_H__
#include "cocos2d.h"
#include "Monster\Monster.h"

class ChiefOfTribe : public Monster {
public:
	virtual bool init();
	CREATE_FUNC(ChiefOfTribe);
	virtual void resetPropoties();
private:
	static const int m_initHp = 30;
};
#endif // !__Slime_H__
