#pragma once
#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"
#include "Entity/Item/Player/Player.h"
#include "FlowWord/FlowWord.h"
#include "cocos2d.h"
using namespace cocos2d;
class Knight :public Player
{
public:
	Knight();
	~Knight();
	virtual bool init()override;
	CREATE_FUNC(Knight);
public:
	virtual Animate* walk()override;
	virtual void skill()override;
	virtual void skillDuration()override;
	virtual void skillEnd()override;
	virtual void die()override;
	virtual Animate* stand()override;
	virtual Point getSkillDirection()override { return this->getPosition(); }
	virtual int whichPlayer()override { return 3; }
	void loadSkillLongRangeListener();
	void loadSkillCloseWeaponListener();
	void determineSkillWeapon();
	void removeSkill();
	void skillChooseWeapon();
protected:
	LongRange* m_skillLongRange = NULL;
	CloseWeapon* m_skillClose = NULL;
	EventListenerTouchOneByOne* m_skillListener = NULL;
	EventListenerMouse* m_skillMouseMove = NULL;
};