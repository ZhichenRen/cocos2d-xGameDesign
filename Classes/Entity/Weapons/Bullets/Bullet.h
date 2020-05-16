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
	bool isUsed()const;
	void setIsUsed(bool status);
protected:
	int m_bullet_range;
	int m_bullet_damage;
	bool m_is_used;
};
#endif
