#include "Entity\Weapons\Weapon.h"

Weapon::Weapon()
{
	m_power_cost = 0;
	m_range = 0;
}

bool Weapon::init()
{
	return true;
}

void Weapon::attack(Point pos)
{

}

int Weapon::getPowerCost()const
{
	return m_power_cost;
}

int Weapon::getRange()const
{
	return m_range;
}

void Weapon::bindMap(AdventureMapLayer* map)
{
	m_map = map;
}

Weapon::~Weapon()
{

}