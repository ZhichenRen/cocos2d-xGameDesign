#include "Pig.h"

bool Pig::init()
{
	setMonsterSpeed(0.5);
	setHp(100);
	setResTrack("Pig.png");
	this->bindSprite(Sprite::create(this->getResTrack()),0.6f,0.6f);
	auto sword = MonsterSword::create();
	//sword->setPosition(this->getPosition());
	setMonsterWeapon(sword);
	this->addChild(sword, 1);
	m_isAlive = true;
	return true;
}

void Pig::resetPropoties() 
{
	show();
	setHp(150);
	m_isAlive = true;
}