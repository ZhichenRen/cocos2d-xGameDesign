#include "Entity\Weapons\RPG.h"
#include "Entity\Weapons\Bullets\ExplosiveBullet.h"

#define PI 3.1415926

bool RPG::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	scheduleUpdate();
	m_power_cost = 5;
	m_bullet_num = 30;
	m_range = 250;
	m_bullet_damage = 10;
	m_bullet_speed = 300;
	m_attack_speed = 0.3f;
	m_explosion_damage = 90;
	m_explosion_range = 20;
	m_bullet_picture = std::string("RPG.png");
	bindSprite(Sprite::create("Fist_of_Heaven.png"), 0.2f, 0.2f);
	scheduleUpdate();
	return true;
}

void RPG::attack(Point pos)
{
	if (m_is_attack == true)
	{
		return;
	}
	if (m_bullet_num == 0)
	{
		return;
	}
	m_is_attack = true;
	m_bullet_num--;
	Point weapon_pos = m_sprite->getPosition();
	Point now = this->convertToWorldSpace(weapon_pos);
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
	}
	getSprite()->setRotation(-degree);
	ExplosiveBullet* new_bullet = ExplosiveBullet::create();
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), 0.3f, 0.3f);
	new_bullet->setInfo(m_range, m_bullet_damage, m_explosion_range, m_explosion_damage);
	auto weapon_rotate_up = RotateBy::create(m_attack_speed / 2, -5);
	auto weapon_rotate_down = RotateBy::create(m_attack_speed / 2, 5);
	auto call_back = CallFunc::create(
		[&]() {
		m_is_attack = false;
	}
	);
	if ((degree > 0 && dy < 0 && dx < 0) || (degree < 0 && dy>0 && dx < 0))
	{
		degree += 180;
		getSprite()->setFlippedX(true);
		auto gun_action = Sequence::create(weapon_rotate_down, weapon_rotate_up, call_back, NULL);
		m_sprite->runAction(gun_action);
	}
	else
	{
		getSprite()->setFlippedX(false);
		auto gun_action = Sequence::create(weapon_rotate_up, weapon_rotate_down, call_back, NULL);
		m_sprite->runAction(gun_action);
	}
	Point origin_pos = Point(getSprite()->getPositionX() + getSprite()->getBoundingBox().size.width*cos(degree / 180 * PI) / 2
		, getSprite()->getPositionY() + getSprite()->getBoundingBox().size.width*sin(degree / 180 * PI) / 2);
	origin_pos = m_map->convertToNodeSpace(convertToWorldSpace(origin_pos));
	new_bullet->setPosition(origin_pos);
	new_bullet->setOriginPos(origin_pos);
	new_bullet->setRotation(-degree);
	new_bullet->setVisible(true);
	m_map->addChild(new_bullet, 2);
	auto move_action = MoveBy::create(1.0f, Vec2(m_bullet_speed*cos(degree / 180 * PI), m_bullet_speed*sin(degree / 180 * PI)));
	auto attack_action = RepeatForever::create(move_action);
	new_bullet->runAction(attack_action);
	m_bullet.push_back(new_bullet);
}