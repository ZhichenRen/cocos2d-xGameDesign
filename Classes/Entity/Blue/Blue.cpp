#include "Entity\Blue\Blue.h"
#define RANDOMRANGE 10


bool Blue::init()
{
	bindSprite(Sprite::create("Blue.png"), 1.0f, 1.0f);
	
	return true;
}

int Blue::getBlueValue()const
{
	return m_blueValue;
}

void Blue::disappear()
{
	m_sprite->setVisible(false);
}

//可以让蓝一直上下跳
void Blue::setRandomPosition()
{
	auto curPosition = getPosition();

	auto ranF1 = CCRANDOM_0_1();
	auto ranF2 = CCRANDOM_0_1();

	auto ranPosition = ccp(curPosition.x + ranF1 * RANDOMRANGE, curPosition.y + ranF2 * RANDOMRANGE);
		//设置一个偏差范围
	this->setPosition(ranPosition);
}
