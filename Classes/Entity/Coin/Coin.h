#ifndef __Coin_H__
#define __Coin_H__

#include "Entity\Entity.h"

class Coin :public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Coin);
public:
	int getPrice()const;
	void disappear();
private:
	int m_price;
};
#endif
