#ifndef __Boss_H__
#define __Boss_H__
#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Weapons\MonsterSword.h"
class Boss : public Monster {
public:
	virtual bool init();
	void resetPropoties();
	CREATE_FUNC(Boss);
private:
	static const int m_initHp = 50;
};
#endif // !__Slime_H__
