#ifndef __GoldenSword_H__
#define __GoldenSword_H__

#include "Entity\Weapons\CloseWeapon.h"

class GoldenSword : public CloseWeapon
{
public:
	virtual bool init();
	CREATE_FUNC(GoldenSword);
	virtual void upgrade();
};

#endif