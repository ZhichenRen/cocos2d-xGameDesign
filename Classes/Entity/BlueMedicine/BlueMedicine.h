#pragma once
#ifndef __BlueMedicine_H__
#define __BlueMedicine_H__

#include "Entity\Entity.h"

class BlueMedicine :public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(BlueMedicine);
public:
	int getBlueMedicineValue()const;
	void disappear();
	void setRandomPosition();
	bool isUsed()const;
private:
	int m_BlueMedicineValue;
	bool m_is_used;
};
#endif
