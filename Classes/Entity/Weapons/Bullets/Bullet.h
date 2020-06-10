#ifndef __Bullet_H__
#define __Bullet_H__

#include "Entity\Entity.h"

class LongRange;

class Bullet :public Entity
{
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	virtual bool init();
public:
	bool isCollideWith(Entity* entity);
	int getRange()const;
	int getDamage()const;
	void setInfo(int range, int damage);
	bool isUsed()const;
	void setIsUsed(bool status);
	void setOriginPos(const Point& pos);
	float getDistance()const;
	void setBulletAction(float degree, int speed);
	void setDegree(float degree);
	float getDegree()const;
	void setCritRate(float rate);
	float getCritRate()const;
protected:
	float m_degree;
	int m_bullet_range;
	int m_bullet_damage=1;
	bool m_is_used;

	float m_crit_rate;

	Point m_origin_pos;//in map coordinate
};
#endif
