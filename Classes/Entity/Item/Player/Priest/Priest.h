#pragma once
#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"
#include "Entity/Item/Player/Player.h"
#include "FlowWord/FlowWord.h"
#include "cocos2d.h"
using namespace cocos2d;
class Priest :public Player
{
public:
	Priest();
	~Priest();
	virtual bool init()override;
	CREATE_FUNC(Priest);
public:
	virtual Animate* walk()override;
	virtual void skill()override;
	virtual void skillDuration()override;
	virtual void skillEnd()override;
	virtual void die()override;
	virtual Animate* stand()override;
	virtual Point getSkillDirection()override { return this->getPosition(); }
	virtual int whichPlayer()override { return 2; }
protected:
	Sprite* m_priestSkill = NULL;
	int m_skillTime;
};