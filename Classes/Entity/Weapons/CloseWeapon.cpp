#include "Entity\Weapons\CloseWeapon.h"

bool CloseWeapon::init()
{
	m_attack_speed = 1.0f;
	m_damage = 1;
	m_is_attack = false;
	m_is_hit = false;
	return true;
}

void CloseWeapon::attack(Point pos)
{
	if (m_is_attack)
	{
		return;
	}
	m_is_attack = true;
	auto rotate_down = RotateBy::create(m_attack_speed / 2, 90);
	auto rotate_up = RotateBy::create(m_attack_speed / 2, -90);
	auto call_back = CallFunc::create(
		[&]() {
		m_is_attack = false;
		m_is_hit = false;
	}
	);
	Point now = convertToWorldSpace(Point(0, 0));
	int dx = pos.x - now.x;
	int dy = pos.y - now.y;
	if (dx < 0)
	{
		m_attack_position = LEFT;
		m_sprite->setFlippedX(true);
		m_sprite->setAnchorPoint(Vec2(1, 0));
		auto attack_action = Sequence::create(rotate_up, rotate_down, call_back, NULL);
		m_sprite->runAction(attack_action);
	}
	else
	{
		m_attack_position = RIGHT;
		m_sprite->setFlippedX(false);
		m_sprite->setAnchorPoint(Vec2(0, 0));
		auto attack_action = Sequence::create(rotate_down, rotate_up, call_back, NULL);
		m_sprite->runAction(attack_action);
	}
}

bool CloseWeapon::isCollideWith(Entity* entity)
{
	auto entity_rect = entity->getBoundingBox();
	Point pos_now = convertToWorldSpace(m_sprite->getPosition());
	Rect weapon_rect;
	if (m_attack_position == RIGHT)
	{
		weapon_rect = Rect(pos_now.x, pos_now.y - m_range, m_range, 2 * m_range);
	}
	else if (m_attack_position == LEFT)
	{
		weapon_rect = Rect(pos_now.x - m_range, pos_now.y - m_range, m_range, 2 * m_range);
	}
	return weapon_rect.intersectsRect(entity_rect);
}

bool CloseWeapon::isAttack()const
{
	return m_is_attack;
}

float CloseWeapon::getCritRate()const
{
	return m_crit_rate;
}

void CloseWeapon::flipped(bool status)
{
	if (status == true)//toward left
	{
		getSprite()->setFlippedX(true);
		getSprite()->setAnchorPoint(Vec2(1.0f, 0.0f));
	}
	else
	{
		getSprite()->setFlippedX(false);
		getSprite()->setAnchorPoint(Vec2(0.0f, 0.0f));
	}
}

bool CloseWeapon::isCloseWeapon()const
{
	return true;
}

int CloseWeapon::getDamage()const
{
	return m_damage;
}

void CloseWeapon::setDamage(int damage)
{
	m_damage = damage;
}

void CloseWeapon::setIsHit(bool status)
{
	m_is_hit = status;
}

bool CloseWeapon::isHit()const
{
	return m_is_hit;
}