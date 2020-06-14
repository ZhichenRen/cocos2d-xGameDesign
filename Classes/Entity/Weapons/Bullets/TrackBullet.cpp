#include "Entity/Weapons/Bullets/TrackBullet.h"
#include "Entity/Item/Player/Player.h"
#include <cmath>
#define PI 3.1415926

bool TrackBullet::init()
{
	if (!Bullet::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

void TrackBullet::update(float dt)
{
	auto pos = getPosition();
	auto player_pos = m_player->getPosition();
	float dx = player_pos.x - pos.x;
	float dy = player_pos.y - pos.y;

	float degree;
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
	}

	if (dx < 0)
	{
		degree += 180;
	}
	m_degree = degree;

	float distance = sqrtf(dx * dx + dy * dy);
	dx = dx / distance * m_bullet_speed / 60.0f;
	dy = dy / distance * m_bullet_speed / 60.0f;
	auto track_action = MoveBy::create(1.0f / 60.0f, Vec2(dx, dy));
	this->runAction(track_action);
}

void TrackBullet::bindPlayer(Entity* player)
{
	m_player = player;
}

void TrackBullet::setBulletSpeed(int speed)
{
	m_bullet_speed = speed;
}