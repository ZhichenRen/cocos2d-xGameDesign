#ifndef __StoneSword_H__
#define __StoneSword_H__

#include "Entity/Weapons/CloseWeapon.h"

class StoneSword :public CloseWeapon
{
public:
	virtual bool init();
	CREATE_FUNC(StoneSword);
	virtual void upgrade();
};

#endif