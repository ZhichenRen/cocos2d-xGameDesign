#ifndef __Bullet_H__
#define __Bullet_H__

#include "Entity\Entity.h"

class Bullet :public Entity
{
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	bool IsCollideWith(Entity* entity);
	virtual bool init();
};
#endif
