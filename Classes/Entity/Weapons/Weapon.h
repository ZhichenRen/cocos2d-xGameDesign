#ifndef __Weapon_H__
#define __Weapon_H__

#include "cocos2d.h"
#include "Entity\Entity.h"
#include "Scene\AdventureMapScene.h"
#include <Entity\Weapons\Bullets\Bullet.h>
USING_NS_CC;

class Weapon :public Entity
{
public:
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
	virtual bool init();
public:
	virtual void attack(Point pos);
	virtual std::vector<Bullet*> getBullet() const;
	int getPowerCost()const;
	int getRange()const;
	void bindMap(AdventureMapLayer* map);
protected:
	int m_power_cost;
	int m_range;
	AdventureMapLayer* m_map;
};
#endif
