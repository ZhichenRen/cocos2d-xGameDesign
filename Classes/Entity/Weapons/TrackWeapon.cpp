#include "Entity/Weapons/TrackWeapon.h"
#include "Entity/Weapons/Bullets/TrackBullet.h"
#include "Entity/Item/Player/Player.h"
bool TrackWeapon::init()
{
	if (!LongRange::init())
	{
		return false;
	}
	m_power_cost = 3;
	m_bullet_num = 100;
	m_range = 100;
	m_bullet_damage = 3;
	m_bullet_speed = 150;
	m_attack_speed = 3.0f;
	m_crit_rate = 0.2f;
	m_bullet_picture = std::string("purple.png");
	bindSprite(Sprite::create("CandyGun!.png"), 0.25f, 0.25f);
	getSprite()->setVisible(false);
	m_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	return true;
}

void TrackWeapon::attack(Point pos)
{
	if (m_is_attack == true)
	{
		return;
	}
	m_is_attack = true;

	TrackBullet* new_bullet = TrackBullet::create();
	new_bullet->bindSprite(Sprite::create(m_bullet_picture.c_str()), 0.8f, 0.8f);
	new_bullet->setPosition(m_map->convertToNodeSpace(getParent()->convertToWorldSpace(getPosition())));
	new_bullet->setVisible(true);
	new_bullet->setBulletSpeed(m_bullet_speed);
	new_bullet->bindPlayer(m_player);
	m_bullet.push_back(new_bullet);
	m_map->addChild(new_bullet);

	auto call_back = CallFunc::create(
		[&]() {
		m_is_attack = false;
	}
	);
	auto gun_action = Sequence::create(DelayTime::create(m_attack_speed), call_back, NULL);
	m_sprite->runAction(gun_action);
}

void TrackWeapon::bindPlayer(Entity* player)
{
	m_player = player;
}