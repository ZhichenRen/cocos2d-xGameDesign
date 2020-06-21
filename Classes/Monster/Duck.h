#ifndef __Duck_H__
#define __Duck_H__
#include "cocos2d.h"
#include "Monster\Monster.h"
#include "Entity\Weapons\MonsterSword.h"
class Duck : public Monster {
public:
	virtual bool init();
	void resetPropoties();
	CREATE_FUNC(Duck);
private:
	static const int m_initHp = 20;
};
#endif // !__Slime_H__
