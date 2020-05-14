#ifndef __Monster_H__
#define __Monster_H__
#include "Entity/Entity.h"
#include "cocos2d.h"
USING_NS_CC;
class Monster :public Entity {
public:
	Monster();
	~Monster();
	virtual bool init();
public:
	void show();
	void hide();
	//void reset();
	bool isAlive();
	void moveTo(const Vec2& targetPosition);
	const int getHp();
	bool getAttacked(const int damage);
	CREATE_FUNC(Monster);
private:
	int m_Hp;
	int m_isAlive;
	int m_runningSpeed;
	Vec2 m_curPosition;
	//Weapon m_Weapon;
};
#endif // !__Monster_H__
