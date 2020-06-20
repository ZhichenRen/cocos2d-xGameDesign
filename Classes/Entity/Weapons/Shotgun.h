#ifndef __Shotgun_H__
#define __Shotgun_H__

#include "Entity\Weapons\LongRange.h"

class Shotgun :public LongRange
{
public:
	CREATE_FUNC(Shotgun);
	virtual bool init();
	virtual void attack(Point pos);
	int getBulletNumAtOnce()const;
	void setBulletNumAtOnce(int new_num);
	float getBulletDegree()const;
	void setBulletDegree(float new_degree);
	virtual void upgrade();
protected:
	int m_bullet_num_at_once;
	float m_degree;//degree beween two bullets
};

#endif