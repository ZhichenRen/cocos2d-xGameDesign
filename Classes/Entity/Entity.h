#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node
{
public:
	Entity();
	~Entity();
	Sprite* GetSprite();
	void BindSprite(Sprite* sprite, float x_scale = 1, float y_scale = 1);
private:
	Sprite* m_sprite_;
};
#endif
