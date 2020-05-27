#ifndef __RPG_H__
#define __RPG_H__

#include "Entity\Weapons\LongRange.h"

class RPG :public LongRange
{
public:
	CREATE_FUNC(RPG);
	virtual bool init();
	virtual void attack(Point pos);
private:
	int m_explosion_range;
	int m_explosion_damage;
};

#endif