#pragma once
#include <algorithm>
#include <vector>
#include "Entity/Weapons/Bullets/Bullet.h"
#include "Entity/Item/Item.h"
#include "Scene/AdventureMapScene.h"
#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"
#include "Entity/Weapons/LongRange.h"
#include "Controller/ControllerListener.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
class Player :public Item
{
public:
	virtual bool init()override;
	void setViewPointByPlayer()const;
	virtual void setTagPosition(const int x, const int y)override;
	bool isCollideWith(Entity* entity);

	virtual void setTiledMap(AdventureMapLayer* map);
	AdventureMapLayer* getMap() { return m_map; }

	inline int getiNowCD()const { return m_iNowCD; }
	void setiNowCD(int cd);
	inline int getiTotalCD()const { return m_iTotalCD; }
	void setiTotalCD(int cd);

	inline int getiNowMp()const { return m_iNowMp; }
	void setiNowMp(int mp);
	inline int getiTotalMp()const { return m_iTotalMp; }
	void setiTotalMp(int mp);

	inline int getiNowSkillDuration()const { return m_iNowSkillDuration; }
	void setiNowSkillDuration(int duration);
	inline int getiTotalSkillDuration()const { return m_iTotalSkillDuration; }
	void setiTotalSkillDuration(int duration);

	int getSkillDirectionX()const { return m_skillDirectionX; }
	int getSkillDirectionY()const { return m_skillDirectionY; }
	void setSkillDirectionX(int x) { m_skillDirectionX = x; }
	void setSkillDirectionY(int y) { m_skillDirectionY = y; }

	void setRightToward();
	void setLeftToward();

	inline bool getIsInSkill() const { return m_isInSkill; }
	void setLongRange(LongRange* longRange);
	std::vector<Bullet*> getBullet()const;
	void hit(int damage);
public:
	virtual Animate* walk() = 0;
	virtual void skill() = 0;
	virtual void skillEnd() = 0;
	virtual void die() = 0;
	virtual Animate* stand() = 0;
	virtual Point& getSkillDirection() = 0;

	int isPositiveOrNegative(int num);
	Point tileCoordForPosition(Point pos);
	inline void setCdBar(LoadingBar* cdBar) { m_cdBar = cdBar; }

	LoadingBar* m_cdBar = NULL;
	std::vector<Bullet*> m_bullet;

protected:
	AdventureMapLayer* m_map;

	int m_iNowCD;
	int m_iTotalCD;
	int m_iNowMp;
	int m_iTotalMp;
	int m_iNowSkillDuration;
	int m_iTotalSkillDuration;
	int m_skillDirectionX = 0;
	int m_skillDirectionY = 0;
	bool m_isInSkill;

	void getBulletFromWeapon();

	LongRange* m_longRange;

private:
	bool m_leftSide = false;
	bool m_rightSide = true;

	inline bool getLeftSide() const { return  m_leftSide; }
	inline bool getRightSide() const { return m_rightSide; }
	inline void setLeftSide(bool aim){ m_leftSide = aim; }
	inline void setRightSide(bool aim) { m_rightSide = aim; }
};
