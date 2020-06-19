#include "Entity/Item/Item.h"

void Item::setiNowHp(int nowHp)
{
	if (nowHp < 0)
		m_iNowHp = 0;
	else if (nowHp > m_iTotalHp)
		m_iNowHp = m_iTotalHp;
	else
		m_iNowHp = nowHp;
}

void Item::setiTotalHp(int nowHp)
{
	if (nowHp < 0)
		m_iTotalHp = 0;
	else
		m_iTotalHp = nowHp;
}

void Item::setController(MyController* controller)
{
	this->m_controller = controller;
	m_controller->setControllerListener(this);
}

void Item::setTagPosition(const int x, const int y)
{
	setPosition(Point(x, y));
}

Point Item::getTagPosition()const
{
	return getPosition();
}