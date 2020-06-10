#ifndef __CHEST_H__
#define __CHEST_H__
#include "cocos2d.h"

USING_NS_CC;
class LongRange;
class Chest : public Node
{
public:
	Chest();
	~Chest();
	void bindSprite(Sprite* chestSprite);
	void setWeapon(int num);
	inline Sprite* getSprite() { return m_chest; }
	inline LongRange* getWeapon() { return m_weapon; }
	CREATE_FUNC(Chest);
private:
	Sprite* m_chest;
	LongRange* m_weapon;
};
#endif
