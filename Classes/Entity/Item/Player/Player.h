#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <array>
#include <typeinfo>
#include "Entity/Weapons/Bullets/Bullet.h"
#include "Entity/Item/Item.h"
#include "AuxiliaryClass/AnimationUtil/AnimationUtil.h"

#include "Entity/Weapons/LongRange.h"
//#include "Entity/Weapons/CloseWeapon.h"
#include "Controller/ControllerListener.h"
#include "Scene/AdventureMapScene.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class CloseWeapon;
class Player :public Item
{
public:
	virtual bool init()override;
	void setViewPointByPlayer();
	virtual void setTagPosition(const int x, const int y)override;
	bool isCollideWith(Entity* entity);

	virtual void setTiledMap(AdventureMapLayer* map);
	AdventureMapLayer* getMap() { return m_map; }

	inline int getiNowCD()const { return m_iNowCD; }
	void setiNowCD(int cd);
	inline int getiTotalCD()const { return m_iTotalCD; }
	void setiTotalCD(int cd);

	inline int getiNowArmor()const { return m_iNowArmor; }
	void setiNowArmor(int armor);
	inline int getiTotalArmor()const { return m_iTotalArmor; }
	void setiTotalArmor(int armor);
	inline int getiArmorCd()const { return m_iArmorCd; }
	void setArmorCd();

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
	void determineWhichWeapon();

	void rangeAttack();

	void hit(int damage);
	void mpDepletion(int mpDe);
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
	inline void setHpBar(LoadingBar* hpBar) { m_hpBar = hpBar; }
	inline void setMpBar(LoadingBar* mpBar) { m_mpBar = mpBar; }
	inline void setArmorBar(LoadingBar* armorBar) { m_armorBar = armorBar; }
	inline bool getLeftSide() const { return  m_leftSide; }
	inline bool getRightSide() const { return m_rightSide; }
	inline void setLeftSide(bool aim) { m_leftSide = aim; }
	inline void setRightSide(bool aim) { m_rightSide = aim; }

	std::vector<Bullet*> getBullet()const;

	LoadingBar* m_cdBar = NULL;
	LoadingBar* m_hpBar = NULL;
	LoadingBar* m_mpBar = NULL;
	LoadingBar* m_armorBar = NULL;
	std::vector<Bullet*> m_bullet;
	bool isAttackingWithCloseWeapon()const;
	void resetWeaponPosition(bool status/*true stands for left and false stands for right*/);

protected:
	AdventureMapLayer* m_map;

	int m_iNowCD;
	int m_iTotalCD;
	int m_iNowMp;
	int m_iTotalMp;
	int m_iNowSkillDuration;
	int m_iNowArmor;
	int m_iTotalArmor;
	int m_iArmorCd;

	int m_iTotalSkillDuration;
	int m_skillDirectionX = 0;
	int m_skillDirectionY = 0;
	bool m_isInSkill;

	void getBulletFromWeapon();


	LongRange* m_longRange = NULL;
	std::array <LongRange*, 10> m_longRangeWeapon;
	std::array <CloseWeapon*, 10> m_closeWeapon;
	std::array <std::string,10> m_weapons;
	int m_numMyWeapon;
	int m_numWeapon;
	int m_numTotalWeapon;
	int m_numLongRangeWeapon;
	int m_numCloseWeapon;

	bool m_is_attacking;
	bool m_is_close_weapon_now;

private:
	bool m_leftSide = false;
	bool m_rightSide = true;
};
