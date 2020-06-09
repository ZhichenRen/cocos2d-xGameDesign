#ifndef __SHOP_H__
#define __SHOP_H__
#include "cocos2d.h"
#include "FlowWord/FlowWord.h"

USING_NS_CC;
class LongRange;

class Shop : public Node
{
public:
	Shop();
	~Shop();
	inline int getPrice() { return m_price; }
	void bindSprite(Sprite* shopSprite);
	void setInteractionNum(int num);
	void setWeapon(int num);
	void showFlowWordFirstMeet();
	void showFlowWordLackMoney();
	void showFlowWordEnoughMoney();
	inline LongRange* getWeapon() { return m_weapon; }
	inline Sprite* getSprite() { return m_shop; }
	inline int getInteractionNum() { return m_interaction; }
	CREATE_FUNC(Shop);
private:
	const int m_price = 20;
	int m_interaction;
	Sprite* m_shop;
	LongRange* m_weapon;
	FlowWord* m_flowWord;
};

#endif // !1

