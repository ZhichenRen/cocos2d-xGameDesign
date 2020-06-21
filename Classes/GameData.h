#ifndef __GAME_DATA__
#define __GAME_DATA__
#include "cocos2d.h"
USING_NS_CC;
#include "Entity/Item/Player/Player.h"

#define SAFEMAP 1
#define ADVMAP 2

class GameData
{
private:
	GameData();
	static GameData* m_pData;
	static int m_coinNum;
	static int m_bgmNum;
	static int m_level;
	static Vec2 m_lastRoomCoord;
	static std::vector<Vec2>m_coord;
	class Garbo
	{
	public:
		~Garbo()
		{
			if (GameData::m_pData)
			{
				delete GameData::m_pData;
			}
		}
	};
	static Garbo m_garbo;
public:
	static GameData* getInstance()
	{
		if (m_pData == nullptr)
		{
			m_pData = new GameData;
		}
		return m_pData;
	}
	static int getCoinNum();
	static void setCoinNum(int coinNum);
	static int getBgmNum();
	static void setBgmNum(int bgmNum);
	static int getLevel();
	static void setLevel(int level);
	static Vec2 getLastRoomCoord();
	static void setLastRoomCoord(Vec2 lastRoomCoord);
	static std::vector<Vec2> getCoord();
};

#endif // !__GAME_DATA__