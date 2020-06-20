
#ifndef __MonsterGun_H__
#define __MonsterGun_H__

#include "Entity\Weapons\LongRange.h"

class MonsterGun :public LongRange
{
public:
	MonsterGun();
	~MonsterGun();
	CREATE_FUNC(MonsterGun);
	virtual bool init();
};

#endif