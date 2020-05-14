#define LOCAL

#ifdef LOCAL
#include "Weapon.h"
#else
#include "Entity\Weapon\Weapon.h"
#endif

Weapon::Weapon()
{
	m_power_cost = 0;
	m_range = 0;
}

bool Weapon::init()
{
	return true;
}

void Weapon::attack()
{

}

Weapon::~Weapon()
{

}