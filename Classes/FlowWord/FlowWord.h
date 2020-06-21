#ifndef __FlowWord_H__
#define __FlowWord_H__

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node
{
public:
	CREATE_FUNC(FlowWord);
	virtual bool init();
	void showWord(const char* text, Point pos);
	void showShopWord(const char* text);
	void showMonsDmg(const char* text, float ySize, float time = 0.2f);
	void showCritDmg(const char* text, float ySize, float time = 0.2f);
	void showMonsTaunted();
private:
	Label* m_message;
};
#endif
