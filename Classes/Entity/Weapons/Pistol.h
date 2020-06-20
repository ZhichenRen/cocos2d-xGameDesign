#ifndef __Pistol_H__
#define __Pistol_H__

#include "Entity/Weapons/LongRange.h"

class Pistol :public LongRange
{
public:
	CREATE_FUNC(Pistol);
	virtual bool init();
	virtual void upgrade();
};

#endif