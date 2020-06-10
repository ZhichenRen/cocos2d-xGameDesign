#include "Entity\Coin\Coin.h"

bool Coin::init()
{
	bindSprite(Sprite::create("Coin.png"), 1.0f, 1.0f);
	m_price = 1;
	m_is_used = false;
	return true;
}

int Coin::getPrice()const
{
	return m_price;
}

void Coin::disappear()
{
	m_sprite->setVisible(false);
	m_is_used = true;
}

bool Coin::isUsed()const
{
	return m_is_used;
}