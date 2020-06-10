#pragma once
#ifndef __Blue_H__
#define __Blue_H__

#include "Entity\Entity.h"

class Blue :public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Blue);
public:
	int getBlueValue()const;
	void disappear();
	void setRandomPosition();

private:
	int m_blueValue;
};
#endif
