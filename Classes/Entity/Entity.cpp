#include "Entity.h"

Entity::Entity()
{
	m_sprite = NULL;
}

Entity::~Entity()
{

};

Sprite* Entity::getSprite()
{
	return this->m_sprite;
}

void Entity::bindSprite(Sprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	m_sprite->setPosition(Point(size.width*0.5f, size.height*0.5f));
	this->setContentSize(size);
}
