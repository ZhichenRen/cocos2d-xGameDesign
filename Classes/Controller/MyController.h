#pragma once
#include "cocos2d.h"
#include "Controller/ControllerListener.h"
using namespace cocos2d;

class MyController :public Node
{
public:
	void setControllerListener(ControllerListener* controllerListener);
	virtual bool getIsChangeWeapon()const { return 0; }
	//Áô¸øºó±ß¸´Ð´µÄ
	inline int getiXSpeed() const { return m_iXSpeed; }
	inline int getiYSpeed() const { return m_iYSpeed; }
	void setiXSpeed(int iSpeed);
	void setiYSpeed(int iSpeed);
protected:
	ControllerListener* m_controllerListener;
	int m_iXSpeed;
	int m_iYSpeed;
};
