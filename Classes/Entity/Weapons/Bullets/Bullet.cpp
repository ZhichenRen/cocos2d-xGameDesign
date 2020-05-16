#include "Entity\Weapons\Bullets\Bullet.h"
#include "Entity\Weapons\LongRange.h"

Bullet::Bullet()
{
	
}

bool Bullet::init()
{
	m_is_used = false;
	return true;
}

bool Bullet::isCollideWith(Entity* entity)
{
	//auto bullet_rect = getBoundingBox();
	//auto pos = convertToWorldSpace(this->getParent()->getPosition());
	//bullet_rect.setRect(bullet_rect.origin.x + pos.x, bullet_rect.origin.y + pos.y, bullet_rect.size.width, bullet_rect.size.height);
	//log("Bullet:%f,%f,%f,%f", bullet_rect.getMinX(), bullet_rect.getMinY(), bullet_rect.getMaxX(), bullet_rect.getMaxY());
	//auto entity_rect = entity->getBoundingBox();
	//auto entity_pos = convertToWorldSpace(entity->getParent()->getPosition());
	////entity_rect.setRect(entity_rect.origin.x + entity_pos.x, entity_rect.origin.y + entity_pos.y, entity_rect.size.width, entity_rect.size.height);
	//log("Monster:%f,%f,%f,%f", entity_rect.getMinX(), entity_rect.getMinY(), entity_rect.getMaxX(), entity_rect.getMaxY());
	return getBoundingBox().intersectsRect(entity->getBoundingBox());
}

int Bullet::getRange()const
{
	return m_bullet_range;
}

int Bullet::getDamage()const
{
	return m_bullet_damage;
}

void Bullet::bindWeapon(LongRange* long_range)
{
	m_bullet_damage = long_range->getDamage();
	m_bullet_range = long_range->getRange();
}

bool Bullet::isUsed()const
{
	return m_is_used;
}

void Bullet::setIsUsed(bool status)
{
	m_is_used = status;
}

Bullet::~Bullet()
{

}