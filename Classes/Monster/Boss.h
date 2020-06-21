
#pragma once

#ifndef __Boss_H__
#define __Boss_H__
#include "cocos2d.h"
#include "Monster\Monster.h"


class Boss : public Monster {
public:
	virtual bool init();
	//virtual void die();
	virtual void hit(int damage, float flyingDegree, bool isCriticalStrike);
	CREATE_FUNC(Boss);
	//virtual void resetPropoties();
private:
	static const int m_initHp = 800;
};
#endif