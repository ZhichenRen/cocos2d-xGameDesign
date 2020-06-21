#include "Bonus/Chest.h"
#include "Entity/Weapons/CandyGun.h"
#include "Entity/Weapons/RPG.h"
#include "Entity/Weapons/Shotgun.h"
#include "Entity/Weapons/GoldenSword.h"

Chest::Chest()
{
	this->bindSprite(Sprite::create("chest.png"));
}

Chest::~Chest()
{
}

void Chest::bindSprite(Sprite* chestSprite)
{
	m_chest = chestSprite;
	this->addChild(m_chest);
}

void Chest::setWeapon(int num)
{
	if (num == 1)
	{
		m_weapon = RPG::create();
	}
	else if (num == 2)
	{
		m_weapon = Shotgun::create();
	}
	else if (num == 3)
	{
		m_weapon = CandyGun::create();
	}
	else
	{
		m_weapon = GoldenSword::create();
	}
}