#ifndef __MonsterSword_H__
#define __MonsterSword_H__

#include "Entity\Weapons\CloseWeapon.h"

class MonsterSword : public CloseWeapon
{
public:
	virtual bool init();
	CREATE_FUNC(MonsterSword);
};

#endif