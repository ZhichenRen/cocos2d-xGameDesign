#ifndef __Long_rangeH__
#define __Long_rangeH__

#include "Entity\Weapons\Weapon.h"

class Bullet;

class LongRange :public Weapon
{
public:
	LongRange();
	~LongRange();
	CREATE_FUNC(LongRange);
	virtual bool init();
public:
	virtual void attack(Point pos);
	void rotate(float time, float degree);
	Vector<Bullet*> getBullet()const;
	int getRange()const;
	int getDamage()const;
protected:
	int m_bullet_speed;//speed of the bullet
	int m_bullet_per_sec;
	int m_bullet_num;
	int m_bullet_damage;
	Vector<Bullet*> m_bullet;
	String m_bullet_picture;
};


#endif
