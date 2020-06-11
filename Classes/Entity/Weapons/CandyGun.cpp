#include "Entity\Weapons\CandyGun.h"

CandyGun::CandyGun()
{

}

bool CandyGun::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	m_power_cost = 3;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 10;
	m_bullet_speed = 750;
	m_attack_speed = 0.1f;
	m_crit_rate = 0.3f;
	m_bullet_picture = std::string("CandyBullet.png");
	bindSprite(Sprite::create("CandyGun!.png"), 0.25f, 0.25f);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	return true;
}

CandyGun::~CandyGun()
{

}