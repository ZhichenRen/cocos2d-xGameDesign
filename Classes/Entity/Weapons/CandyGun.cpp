#include "Entity\Weapons\CandyGun.h"

CandyGun::CandyGun()
{

}

bool CandyGun::init()
{	
	power_cost_ = 5;
	bullet_num_ = 100;
	range_ = 100;
	bullet_speed_ = 500;
	bullet_per_sec_ = 2;
	bullet_picture_ = String("CandyBullet.png");
	BindSprite(Sprite::create("CandyGun!.png"), 0.6f, 0.6f);
	return true;
}

CandyGun::~CandyGun()
{

}