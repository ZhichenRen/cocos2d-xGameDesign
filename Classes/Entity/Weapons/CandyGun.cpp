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
	m_attack_speed = 0.2f;
	m_bullet_picture = std::string("CandyBullet.png");
	bindSprite(Sprite::create("CandyGun!.png"), 0.6f, 0.6f);
	return true;
}

CandyGun::~CandyGun()
{

}