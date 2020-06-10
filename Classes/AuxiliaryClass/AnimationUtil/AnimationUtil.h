#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class AnimationUtil
{
public:
	static Animation* createWithSingleFrameName(const char* address, const char* name, float delay, int iLoops);
	static Animation* createWithFrameNameAndNum(const char* address, const char* name, int iNum, float delay, int iLoops);
	static Animation* createWithFrameNameAndNumUsingPlist(const char* address, const char* name, int iNum, float delay, int iLoops);
};
