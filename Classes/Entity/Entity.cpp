#include "Entity.h"

Entity::Entity()
{
	m_sprite_ = NULL;
}

Entity::~Entity()
{

};

Sprite* Entity::getSprite()
{
	return this->m_sprite_;
}

void Entity::bindSprite(Sprite* sprite, float x_scale, float y_scale)
{
	this->m_sprite_ = sprite;
	this->addChild(m_sprite_);
	m_sprite_->setScale(x_scale, y_scale);
	Size size = m_sprite_->getBoundingBox().size;
	m_sprite_->setPosition(Point(0, 0));
	this->setContentSize(size);
}

