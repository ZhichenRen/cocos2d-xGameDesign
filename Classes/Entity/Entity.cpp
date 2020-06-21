#include "Entity\Entity.h"

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

void Entity::bindSprite(Sprite* sprite, float x_scale, float y_scale)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);
	m_sprite->setScale(x_scale, y_scale);
	Size size = m_sprite->getBoundingBox().size;
	m_sprite->setPosition(Point(0, 0));
	this->setContentSize(size);
}

Rect Entity::getBoundingBox()
{
	Rect rect = Rect(0, 0, Node::getBoundingBox().size.width, Node::getBoundingBox().size.height);
	return RectApplyAffineTransform(rect, m_sprite->getNodeToWorldAffineTransform());
}

