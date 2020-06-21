#ifndef __CHEST_H__
#define __CHEST_H__
#include "cocos2d.h"

USING_NS_CC;
class Weapon;

class Chest : public Node
{
public:
	Chest();
	~Chest();
	void bindSprite(Sprite* chestSprite);
	void setWeapon(int num);
	inline Sprite* getSprite() { return m_chest; }
	inline Weapon* getWeapon() { return m_weapon; }
	CREATE_FUNC(Chest);
private:
	Sprite* m_chest;
	Weapon* m_weapon;
};
#endif