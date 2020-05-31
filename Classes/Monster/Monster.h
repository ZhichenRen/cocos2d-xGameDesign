#ifndef __Monster_H__
#define __Monster_H__
#include "Entity/Entity.h"
#include "cocos2d.h"
#include "Entity\Coin\Coin.h"
#include "Entity\Weapons\MonsterGun.h"
USING_NS_CC;
class Monster :public Entity {
public:
	Monster();
	~Monster();
	virtual bool init();
	CREATE_FUNC(Monster);
public:
	void show();
	void hide();
	bool isAlive();
	void moveTo(const Vec2& targetPosition);
	void moveBy(const Vec2& distance);
	bool getAttacked(const int damage);
	void die();
	CC_SYNTHESIZE(float, m_fSpeed, MonsterSpeed);
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(std::string, m_resTrack, ResTrack);
	CC_SYNTHESIZE(bool, m_isAlive);
	CC_SYNTHESIZE(Weapon*, m_weapon, MonsterWeapon);
private:
	
};
#endif // !__Monster_H__
