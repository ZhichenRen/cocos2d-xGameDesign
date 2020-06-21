#ifndef __RPG_H__
#define __RPG_H__

#include "Entity\Weapons\LongRange.h"
#include "Entity\Weapons\Bullets\ExplosiveBullet.h"

class RPG :public LongRange
{
public:
	CREATE_FUNC(RPG);
	virtual bool init();
	virtual void attack(Point pos);
	virtual void upgrade();
protected:
	ExplosiveBullet* generateExplosiveBullet(float degree, float scale_x, float scale_y);
private:
	int m_explosion_range;
	int m_explosion_damage;
};

#endif