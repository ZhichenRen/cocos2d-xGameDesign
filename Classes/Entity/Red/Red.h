#ifndef __Red_H__
#define __Red_H__

#include "Entity\Entity.h"

class Red :public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Red);
public:
	int getRedValue()const;
	void disappear();
	void setRandomPosition();
	bool isUsed()const;

private:
	int m_RedValue;
	bool m_is_used;
};
#endif
