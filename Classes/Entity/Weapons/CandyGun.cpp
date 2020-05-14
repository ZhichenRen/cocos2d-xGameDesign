#include "Entity\Weapons\CandyGun.h"

CandyGun::CandyGun()
{

}

bool CandyGun::init()
{	
	m_power_cost = 5;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_speed = 500;
	m_bullet_per_sec = 2;
	m_bullet_picture = String("CandyBullet.png");
	bindSprite(Sprite::create("CandyGun!.png"), 0.6f, 0.6f);
	return true;
}

CandyGun::~CandyGun()
{

}