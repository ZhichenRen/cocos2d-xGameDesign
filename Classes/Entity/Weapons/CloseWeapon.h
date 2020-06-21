#ifndef __CloseWeapon_H__
#define __CloseWeapon_H__

#include "Entity\Weapons\Weapon.h"
#define RIGHT 1
#define LEFT 2

class CloseWeapon :public Weapon
{
public:
	virtual bool init();
	CREATE_FUNC(CloseWeapon);
public:
	virtual void attack(Point pos);
	bool isCollideWith(Entity* entity);
	bool isAttack()const;
	float getCritRate()const;
	virtual void flipped(bool status);
	virtual bool isCloseWeapon()const override;
	int getDamage()const;
	void setDamage(int damage);
	void setIsHit(bool status);
	bool isHit()const;
protected:
	int m_damage;
private:
	bool m_is_attack;
	int m_attack_position;
	bool m_is_hit;
};


#endif