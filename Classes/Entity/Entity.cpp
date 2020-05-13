#include "Entity.h"

Entity::Entity()
{
	m_sprite_ = NULL;
}

Entity::~Entity()
{

};

Sprite* Entity::GetSprite()
{
	return this->m_sprite_;
}

void Entity::BindSprite(Sprite* sprite, float x_scale, float y_scale)
{
	this->m_sprite_ = sprite;
	this->addChild(m_sprite_);
	m_sprite_->setScale(x_scale, y_scale);
	Size size = m_sprite_->getContentSize();
	m_sprite_->setPosition(Point(size.width*0.5f, size.height*0.5f));
	this->setContentSize(size);
}

