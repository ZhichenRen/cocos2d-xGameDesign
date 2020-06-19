#ifndef __TrackBullet_H__
#define __TrackBullet_H__

#include "Entity/Weapons/Bullets/Bullet.h"

class Player;
class TrackBullet :public Bullet
{
public:
	virtual bool init();
	virtual void update(float dt);
	void bindPlayer(Entity* player);
	void setBulletSpeed(int speed);
	CREATE_FUNC(TrackBullet);
private:
	Entity* m_player = NULL;
	int m_bullet_speed;
};


#endif