#include "GameData.h"


int GameData::m_coinNum = 0;
int GameData::m_level = 1;
Vec2 GameData::m_lastRoomCoord = Vec2(2, 2);
GameData* GameData::m_pData = nullptr;
GameData::Garbo GameData::m_garbo;
std::vector<Vec2> GameData::m_coord = { 
	Vec2(11,11), Vec2(52,11), Vec2(93,11), Vec2(134,11), Vec2(175,11), 
	Vec2(11,52), Vec2(52,52), Vec2(93,52), Vec2(134,52), Vec2(175,52),
	Vec2(11,93), Vec2(52,93), Vec2(93,93), Vec2(134,93), Vec2(175,93),
	Vec2(11,134), Vec2(52,134), Vec2(93,134), Vec2(134,134), Vec2(175,134),
	Vec2(11,175), Vec2(52,175), Vec2(93,175), Vec2(134,175), Vec2(175,175)};
//{
//	{11, 11}, { 52,11 }, { 93,11 }, { 134,11 }, { 175,11 },
//	{ 11,52 }, { 52,52 }, { 93,52 }, { 134,52 }, { 175,52 },
//	{ 11,93 }, { 52,93 }, { 93,93 }, { 134,93 }, { 175,93 },
//	{ 11,134 }, { 52,134 }, { 93,134 }, { 134,134 }, { 175,134 },
//	{ 11,175 }, { 52,175 }, { 93,175 }, { 134,175 }, { 175,175 } }

int GameData::getCoinNum()
{
	return m_coinNum;
}

void GameData::setCoinNum(int coinNum)
{
	m_coinNum = coinNum;
}

int GameData::getLevel()
{
	return m_level;
}

void GameData::setLevel(int level)
{
	m_level = level;
}


Vec2 GameData::getLastRoomCoord()
{
	return m_lastRoomCoord;
}

void GameData::setLastRoomCoord(Vec2 lastRoomCoord)
{
	m_lastRoomCoord = lastRoomCoord;
}

std::vector<Vec2> GameData::getCoord()
{
	return m_coord;
}
