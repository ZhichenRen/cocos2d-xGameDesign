#include "Entity/Entity.h"
class Actor :public Entity {
public:
	//CREATE_FUNC(Actor);
	virtual bool init();

	virtual void moveTo(const Vec2& targetPosition);
	virtual int getHp() const { return m_Hp; };
	virtual bool getAttacked(const int damage);
	virtual bool attack() = 0;
	/*virtual bool takeDebuff(Buff buff);
	virtual Buff getCurBuff();*/
private:
	int m_Hp;
	Vec2 m_curPosition;
};