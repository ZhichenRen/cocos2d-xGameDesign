#ifndef __Traveller_H__
#define __Traveller_H__
#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Weapons\MonsterSword.h"
class Traveller : public Monster {
public:
	virtual bool init();
	void resetPropoties();
	CREATE_FUNC(Traveller);
private:
	static const int m_initHp = 25;
};
#endif // !__Slime_H__