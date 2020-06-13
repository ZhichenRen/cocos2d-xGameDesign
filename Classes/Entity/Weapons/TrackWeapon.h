#ifndef __TrackWeapon_H__
#define __TrackWeapon_H__

#include "Entity/Weapons/LongRange.h"

class Player;
class TrackWeapon :public LongRange
{
public:
	virtual bool init();
	CREATE_FUNC(TrackWeapon);
	virtual void attack(Point pos);
	void bindPlayer(Entity* player);
private:
	Entity* m_player = NULL;
};

#endif