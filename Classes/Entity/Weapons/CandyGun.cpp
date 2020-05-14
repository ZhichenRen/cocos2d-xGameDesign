#include "Entity\Weapons\CandyGun.h"

CandyGun::CandyGun()
{

}

bool CandyGun::init()
{	
	power_cost_ = 5;
	bullet_num_ = 100;
	range_ = 100;
	bullet_speed_ = 100;
	bullet_per_sec_ = 2;
	bullet_picture_ = String("CandyGunBullet.png");
	BindSprite(Sprite::create("CandyGun.png"), 0.3f, 0.3f);
	return true;
}

CandyGun::~CandyGun()
{

}