#define LOCAL

#ifdef LOCAL
#include "Weapon.h"
#else
#include "Entity\Weapon\Weapon.h"
#endif

Weapon::Weapon()
{
	power_cost_ = 0;
	range_ = 0;
}

bool Weapon::init()
{
	return true;
}

void Weapon::Attack()
{

}

Weapon::~Weapon()
{

}