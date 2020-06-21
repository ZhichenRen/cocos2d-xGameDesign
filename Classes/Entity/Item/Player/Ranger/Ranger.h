#pragma once
#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"
#include "Entity/Item/Player/Player.h"
#include "cocos2d.h"
#include "Scene/DeathScene.h"
using namespace cocos2d;
class Ranger :public Player
{
public:
	Ranger();
	~Ranger();
	virtual bool init()override;
	CREATE_FUNC(Ranger);
public:
	virtual Animate* walk()override;
	virtual void skill()override;
	virtual void skillDuration() override{ return; }
	virtual void skillEnd()override;
	virtual void die()override;
	virtual Animate* stand()override;
	virtual Point getSkillDirection()override;
	virtual int whichPlayer()override { return 1; }
protected:
};