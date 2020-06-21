#ifndef __BossGun_H__
#define __BossGun_H__

#include "Entity/Weapons/Shotgun.h"

class BossGun :public Shotgun
{
public:
	virtual bool init();
	CREATE_FUNC(BossGun);
};
#endif