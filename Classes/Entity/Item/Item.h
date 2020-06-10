#pragma once
#include "Entity/Entity.h"
#include "Controller/MyController.h"
#include "Controller/ControllerListener.h"
#include "cocos2d.h"
using namespace cocos2d;
class Item :public Entity, public ControllerListener
{
public:
	inline int getiNowHp() const { return m_iNowHp; }
	void setiNowHp(int nowHp);
	inline int getiTotalHp() const { return m_iTotalHp; }
	void setiTotalHp(int nowHp);
	void setController(MyController* controller);
	MyController* getController()const { return m_controller; }
	virtual void setTagPosition(const int x, const int y) override;
	virtual Point getTagPosition()const;
protected:
	int m_iNowHp;
	int m_iTotalHp;
	MyController* m_controller;
};