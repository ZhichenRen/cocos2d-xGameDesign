#include "Entity\Coin\Coin.h"

bool Coin::init()
{
	bindSprite(Sprite::create("Coin.png"), 1.0f, 1.0f);
	return true;
}

int Coin::getPrice()const
{
	return m_price;
}

void Coin::disappear()
{
	m_sprite->setVisible(false);
}