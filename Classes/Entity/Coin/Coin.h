#ifndef __Coin_H__
#define __Coin_H__

#include "Entity\Entity.h"

class Coin :public Entity
{
public:
	virtual bool init();
	void setRandomPosition();
	CREATE_FUNC(Coin);
public:
	int getPrice()const;
	void disappear();
	bool isUsed()const;
private:
	int m_price;
	bool m_is_used;
};
#endif
