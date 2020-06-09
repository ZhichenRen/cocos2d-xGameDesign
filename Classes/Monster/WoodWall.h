#ifndef __WoodWall_H__
#define __WoodWall_H__
#include "cocos2d.h"
#include "Monster\Monster.h"
class WoodWall : public Monster {
public:
	virtual bool init();
	//void resetPropoties();
	virtual void hit(int damage, float flyingDegree, bool isCriticalStrike);
	//void cancelPreRec();
	CREATE_FUNC(WoodWall);
private:
	static const int m_initHp = 100;
};
#endif // !__Slime_H__
