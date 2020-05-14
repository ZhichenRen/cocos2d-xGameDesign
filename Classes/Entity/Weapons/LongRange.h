#ifndef __LongRange_H__
#define __LongRange_H__

#include "Entity\Weapons\Weapon.h"
#include "Entity\Weapons\Bullets\Bullet.h"

class LongRange :public Weapon
{
public:
	LongRange();
	~LongRange();
	CREATE_FUNC(LongRange);
	virtual bool init();
	virtual void Attack(Point pos);
	void Rotate(float time, float degree);
protected:
	int bullet_speed_;//speed of the bullet
	int bullet_per_sec_;
	int bullet_num_;
	Vector<Bullet*> bullet_;
	String bullet_picture_;
};

#endif
