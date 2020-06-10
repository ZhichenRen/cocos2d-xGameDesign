#ifndef __ExplosiveBullet_H__
#define __ExplosiveBullet_H__

#include "Entity\Weapons\Bullets\Bullet.h"

class ExplosiveBullet :public Bullet
{
public:
	CREATE_FUNC(ExplosiveBullet);
	virtual bool init();
	void explode();
	int getExplosionDamage()const;
	int getExplosionRange()const;
	void setInfo(int range, int damage, int explosion_range, int explosion_damage);
	bool isExplode()const;
private:
	int m_explosion_damage;
	int m_explosion_range;
	bool m_is_explode;
	void explosionCallback();
};

#endif
