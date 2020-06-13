#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ControllerListener
{
public:
	virtual void setTagPosition(const int x, const int y) = 0;
	virtual Point getTagPosition()const = 0;
};