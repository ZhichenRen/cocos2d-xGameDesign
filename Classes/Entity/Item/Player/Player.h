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

	void setWeapon(std::string& str, const bool isUpgrate=false);
	void chooseWeapon();
	void chooseAbondonWeapon();
	void determineWhichWeapon();
	void loadLongRangeListener();
	void loadCloseWeaponListener();
	void resetWeapon();
	void changeWeapon();
	int findWhichLongRange()const;
	void abandonWeapon();
	void getBuff(int i);

	void hit(int damage);
	void mpDepletion(int mpDe);

	const std::string& getWeaponFileName(){ return m_weaponFileName; }
	int getWeaponPowerCost() { return m_weaponPowerCost; }
public:
	virtual Animate* walk() = 0;
	virtual void skill() = 0;
	virtual void skillDuration() = 0;
	virtual void skillEnd() = 0;
	virtual void die() = 0;
	virtual Animate* stand() = 0;
	virtual Point getSkillDirection() = 0;
	virtual int whichPlayer() = 0;

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
	inline bool getIsDeath() { return m_isDeath; }
	inline void setIsDeath(bool isDeath) { m_isDeath = isDeath; }

	inline int getNumWeapon() { return m_numWeapon; }
	inline void setNumWeapon(int num) { m_numWeapon = num; }
	inline int getNumHasWeapon() { return m_numHasWeapon; }
	inline void setNumHasWeapon(int num) { m_numHasWeapon = num; }
	inline int getNumTotalWeapon() { return m_numTotalWeapon; }
	inline void setNumTotalWeapon(int num) { m_numTotalWeapon = num; }
	inline int getLongRange() { return m_numLongRange; }
	inline void setLongRange(int num) { m_numLongRange = num; }


	const std::array <std::string, 10>& getWeaponList() { return m_weapons; }
	void setWeaponList(std::array <std::string, 10>& array) { m_weapons = array; }
	std::array <bool, 10> getIsUpgrate(){ return m_isUpgrate; }
	void setIsUpgrate(std::array <bool, 10>& grate) { m_isUpgrate = grate; }
	std::array <LongRange*, 5> getLongRanges(){ return m_longRanges; }
	void setLongRanges(std::array <LongRange*, 5> longRange) { m_longRanges=longRange; }


	std::vector<Bullet*> getBullet();

	LoadingBar* m_cdBar = NULL;
	LoadingBar* m_hpBar = NULL;
	LoadingBar* m_mpBar = NULL;
	LoadingBar* m_armorBar = NULL;
	std::vector<Bullet*> m_bullet;
	bool isAttackingWithCloseWeapon()const;
	void resetWeaponPosition(bool status/*true stands for left and false stands for right*/);
	CloseWeapon* getCloseWeapon()const;
	LongRange* getLongrange()const;
	bool isClose()const;
	void setInvincible(float duration_time);
	bool isInvincible()const;
	int getDamageBonus()const;
	void setDamageBonus(int bonus_time, float duration);
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

	std::string m_weaponFileName;
	int m_weaponPowerCost;

	void getBulletFromWeapon();

	LongRange* m_longRange = NULL;
	CloseWeapon* m_close = NULL;
	LongRange* m_longRangeAbondon = NULL;
	CloseWeapon* m_closeAbondon = NULL;
	EventListenerTouchOneByOne* m_listener;
	EventListenerMouse* m_mouseMove;
	std::array <std::string, 10> m_weapons{" "};
	std::array <bool, 10> m_isUpgrate{ false };
	std::array <LongRange*, 5> m_longRanges{ NULL };
	int m_numWeapon;
	int m_numHasWeapon;
	int m_numTotalWeapon;
	int m_numLongRange;

	bool m_is_attacking;
	bool m_is_close_weapon_now;
	bool m_isDeath = false;
	bool m_is_invincible = false;
	bool m_isKightSkill = false;

	ParticleFlower* upgrade_effect;
	Sprite* m_shield;
private:
	bool m_leftSide = false;
	bool m_rightSide = true;
	int m_damage_bonus = 1;
};