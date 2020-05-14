#ifndef __Weapon_H__
#define __Weapon_H__

#include "cocos2d.h"
#include "Entity\Entity.h"
USING_NS_CC;

class Weapon :public Entity
{
public:
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
	virtual bool init();
	virtual void attack();
protected:
	int m_power_cost;
	int m_range;
};
#endif
