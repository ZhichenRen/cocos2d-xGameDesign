#ifndef __PlayerChoose_H__
#define __PlayerChoose_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class SafeMapLayer;

struct PlayerInfomation
{
	int hp;
	int armor;
	int mp;
	std::string name;
	std::string ability_name;
	std::string ability_discription;
	std::string image_file;
	std::string ability_image_file;
};

class PlayerChoose :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PlayerChoose);
	void bindMap(SafeMapLayer* safeMap);
	void setPlayer(Ref*, TouchEventType type);
	void back(Ref*, TouchEventType type);
	void setPlayerInformation(const PlayerInfomation& player_information);
protected:
	void loadUI();
	SafeMapLayer* m_safeMap;
	Text* m_hp;
	Text* m_armor;
	Text* m_mp;
	Text* m_name;
	Text* m_ability_name;
	Text* m_ability_discription;
	ImageView* m_image_file;
	ImageView* m_ability_image;
};

#endif