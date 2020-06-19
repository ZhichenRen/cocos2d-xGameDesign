#ifndef __Long_rangeH__
#define __Long_rangeH__

#include "Entity\Weapons\Weapon.h"

class Bullet;

class LongRange :public Weapon
{
public:
	LongRange();
	~LongRange();
	CREATE_FUNC(LongRange);
	virtual bool init();
public:
	virtual void attack(Point pos);
	bool isAttacking();
	std::vector<Bullet*> getBullet()const;
	int getDamage()const;
	void setDamage(int damage);
	virtual void flipped(bool status);
	virtual void setRotationByPos(Point pos);
	virtual void update(float dt);
	virtual bool isCloseWeapon()const override;
protected:
	int m_bullet_speed;//speed of the bullet
	int m_bullet_num;
	int m_bullet_damage;
	std::vector<Bullet*> m_bullet;
	std::string m_bullet_picture;
	bool m_is_attack;
	void adjustWeaponPosition(float degree, bool is_flipped);
	virtual Bullet* generateBullet(float degree, float scale_x, float scale_y);
};


#endif