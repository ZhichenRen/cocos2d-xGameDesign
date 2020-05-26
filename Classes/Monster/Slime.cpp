#include "Slime.h"

bool Slime::init()
{
	setMonsterSpeed(0.1);
	setHp(-1);
	setResTrack("Slime.png");
	m_isAlive = true;
	return true;
}

