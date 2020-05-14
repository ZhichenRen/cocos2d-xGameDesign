#include "Entity\Weapons\Bullets\Bullet.h"

Bullet::Bullet()
{
	
}

bool Bullet::init()
{
	return true;
}

bool Bullet::IsCollideWith(Entity* entity)
{
	return GetSprite()->getBoundingBox().intersectsRect(entity->GetSprite()->getBoundingBox());
}

Bullet::~Bullet()
{

}