#ifndef __CandyGun_H__
#define __CandyGun_H__

#include "Entity\Weapons\LongRange.h"

class CandyGun :public LongRange
{
public:
	CandyGun();
	~CandyGun();
	CREATE_FUNC(CandyGun);
	virtual bool init();
	virtual void upgrade();
};

#endif
