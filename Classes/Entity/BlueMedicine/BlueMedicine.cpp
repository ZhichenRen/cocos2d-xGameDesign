#include "Entity\BlueMedicine\BlueMedicine.h"
#define RANDOMRANGE 100


bool BlueMedicine::init()
{
	bindSprite(Sprite::create("BlueMedicine.png"), 1.0f, 1.0f);
	m_BlueMedicineValue = 60;
	m_is_used = false;
	return true;
}

int BlueMedicine::getBlueMedicineValue()const
{
	return m_BlueMedicineValue;
}

void BlueMedicine::disappear()
{
	m_sprite->setVisible(false);
	m_is_used = true;
}

//可以让蓝一直上下跳
void BlueMedicine::setRandomPosition()
{
	auto curPosition = getPosition();

	auto ranF1 = CCRANDOM_0_1();
	auto ranF2 = CCRANDOM_0_1();
	auto xDif = ranF1 * RANDOMRANGE * 2 - RANDOMRANGE;
	auto yDif = ranF2 * RANDOMRANGE * 2 - RANDOMRANGE;
	auto ranPosition = ccp(curPosition.x + xDif, curPosition.y + yDif);
	//设置一个偏差范围
	this->setPosition(ranPosition);
}

bool BlueMedicine::isUsed()const
{
	return m_is_used;
}
