#include "Entity\Coin\Coin.h"
#define RANDOMRANGE 200
bool Coin::init()
{
	bindSprite(Sprite::create("Coin.png"), 1.0f, 1.0f);
	m_price = 1;
	m_is_used = false;
	return true;
}

void Coin::setRandomPosition()
{
	auto curPosition = getPosition();

	auto ranF1 = CCRANDOM_0_1();
	auto ranF2 = CCRANDOM_0_1();
	auto xDif = ranF1 * RANDOMRANGE * 2 - RANDOMRANGE;
	auto yDif = ranF2 * RANDOMRANGE * 2 - RANDOMRANGE;
	auto ranPosition = ccp(curPosition.x + xDif, curPosition.y + yDif);
	//ÉèÖÃÒ»¸öÆ«²î·¶Î§
	this->setPosition(ranPosition);
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