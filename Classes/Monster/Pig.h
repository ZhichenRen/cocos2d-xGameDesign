#ifndef __Pig_H__
#define __Pig_H__
#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Weapons\MonsterSword.h"
class Pig : public Monster {
public:
	virtual bool init();
	void resetPropoties();
	CREATE_FUNC(Pig);
private:
	static const int m_initHp = 30;
};
#endif // !__Slime_H__
