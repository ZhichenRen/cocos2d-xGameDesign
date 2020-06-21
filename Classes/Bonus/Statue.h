#ifndef __STATUE_H__
#define __STATUE_H__
#include "cocos2d.h"
#include "FlowWord/FlowWord.h"

USING_NS_CC;
class Statue :public Node
{
public:
	Statue();
	~Statue();
	inline int getPrice() { return m_price; }
	void bindSprite(Sprite* statueSprite);
	void setInteractionNum(int num);
	void showFlowWordFirstMeet();
	void showFlowWordLackMoney();
	void showFlowWordEnoughMoney();
	inline int getInteractionNum() { return m_interaction; }
	CREATE_FUNC(Statue);
private:
	const int m_price = 15;
	int m_interaction;
	Sprite* m_statue;
	FlowWord* m_flowWord;
};

#endif // !__STATUE_H__
