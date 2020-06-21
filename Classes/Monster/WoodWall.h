#ifndef __WoodWall_H__
#define __WoodWall_H__
#include "cocos2d.h"
#include "Monster\Monster.h"
class WoodWall : public Monster {
public:
	virtual bool init();
	virtual void hit(int damage, float flyingDegree, bool isCriticalStrike);
	CREATE_FUNC(WoodWall);
private:
	static const int m_initHp = 35;
};
#endif // !__Slime_H__