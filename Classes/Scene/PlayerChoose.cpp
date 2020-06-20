#include "Scene/PlayerChoose.h"
#include "Scene//SafeMapScene.h"
#pragma execution_character_set("utf-8")

bool PlayerChoose::init()
{
	if (!Layer::init())
	{
		return false;
	}
	loadUI();
	return true;
}

void PlayerChoose::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("PlayerInfo_1.ExportJson");
	this->addChild(UI, 0, 0);
	auto back_button = (Button*)Helper::seekWidgetByName(UI, "back_button");
	back_button->addTouchEventListener(this, toucheventselector(PlayerChoose::back));
	auto choose_button = (Button*)Helper::seekWidgetByName(UI, "choose_button");
	choose_button->addTouchEventListener(this, toucheventselector(PlayerChoose::setPlayer));

	m_hp = (Text*)Helper::seekWidgetByName(UI, "hp_label");
	m_mp = (Text*)Helper::seekWidgetByName(UI, "magic_label");
	m_armor = (Text*)Helper::seekWidgetByName(UI, "armor_label");
	m_name = (Text*)Helper::seekWidgetByName(UI, "name_label");
	m_ability_name = (Text*)Helper::seekWidgetByName(UI, "ability_name");
	m_ability_discription = (Text*)Helper::seekWidgetByName(UI, "ability_description");
	m_image_file = (ImageView*)Helper::seekWidgetByName(UI, "player_image");
	m_ability_image = (ImageView*)Helper::seekWidgetByName(UI, "ability_image");
}

void PlayerChoose::bindMap(SafeMapLayer* safeMap)
{
	m_safeMap = safeMap;
}

void PlayerChoose::setPlayer(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		m_safeMap->setPlayer(SafeMapLayer::whichPlayer());
		this->removeFromParentAndCleanup(true);
		break;
	}
}

void PlayerChoose::back(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		this->removeFromParentAndCleanup(true);
		break;
	}
}

void PlayerChoose::setPlayerInformation(const PlayerInfomation& player_information)
{
	m_hp->setText(std::to_string(player_information.hp) + "/" + std::to_string(player_information.hp));
	m_mp->setText(std::to_string(player_information.mp) + "/" + std::to_string(player_information.mp));
	m_armor->setText(std::to_string(player_information.armor) + "/" + std::to_string(player_information.armor));
	m_name->setText(player_information.name);
	m_ability_name->setText(player_information.ability_name);
	m_ability_discription->setText(player_information.ability_discription);
	m_ability_image->loadTexture(player_information.ability_image_file);
	m_image_file->loadTexture(player_information.image_file);
}