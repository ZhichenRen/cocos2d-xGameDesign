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
	void bindWeapon(LongRange* long_range);
protected:
	int m_bullet_range;
	int m_bullet_damage;
};
#endif
