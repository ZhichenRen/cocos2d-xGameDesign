#include "Entity\Weapons\LongRange.h"
#include <cmath>
#define PI 3.1415926

LongRange::LongRange()
{
	bullet_speed_ = 1;
	bullet_per_sec_ = 1;
	bullet_num_ = 1;
}

bool LongRange::init()
{
	return true;
}

void LongRange::Attack(Point pos)
{
	if (bullet_num_ == 0)
	{
		return;
	}

	Point now = convertToWorldSpace(GetSprite()->getPosition());
	float degree;
	float dx = pos.x - now.x;
	float dy = pos.y - now.y;
	if (dx == 0)
	{
		if (dy > 0)
		{
			degree = 90.0f;
		}
		else
		{
			degree = -90.0f;
		}
	}
	else
	{
		degree = atan(dy / dx) / PI * 180;
		if (degree < 0 && dy>0 && dx < 0)
		{
			degree += 180;
		}
		else if (degree < 0 && dy < 0 && dx>0)
		{
			degree += 360;
		}
		else if (degree > 0 && dy < 0 && dx < 0)
		{
			degree += 180;
		}
	}
	GetSprite()->setRotation(-degree);
	Bullet* new_bullet = Bullet::create();
	new_bullet->BindSprite(Sprite::create(bullet_picture_.getCString()),0.2f,0.2f);
	new_bullet->setPosition(GetSprite()->getPositionX() + GetSprite()->getBoundingBox().size.width*cos(degree / 180 * PI) / 2
		, GetSprite()->getPositionY() + GetSprite()->getBoundingBox().size.height*sin(degree / 180 * PI) / 2);
	new_bullet->setRotation(-degree);
	new_bullet->setVisible(true);
	this->addChild(new_bullet);
	auto move_action = MoveBy::create(1.0f, Vec2(bullet_speed_*cos(degree/180*PI), bullet_speed_*sin(degree/180*PI)));
	auto attack_action = RepeatForever::create(move_action);
	new_bullet->runAction(attack_action);
	bullet_.pushBack(new_bullet);
}

void LongRange::Rotate(float time, float degree)
{
	auto rotate_action = RotateTo::create(time, degree);
	GetSprite()->runAction(rotate_action);
}

LongRange::~LongRange()
{

}