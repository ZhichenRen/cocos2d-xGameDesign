#include "Entity/Item/Player/Player.h"

bool Player::init()
{
	return true;
}

bool Player::isCollideWith(Entity* entity)
{
	return getBoundingBox().intersectsRect(entity->getBoundingBox());
}

void Player::setViewPointByPlayer()const
{
	if (m_sprite == NULL)
		return;
	Layer* parent = (Layer*)getParent();
	Size mapTiledNum = m_map->getMap()->getMapSize();
	Size tiledSize = m_map->getMap()->getTileSize();

	Size mapSize = Size(mapTiledNum.width * tiledSize.height, mapTiledNum.height * tiledSize.height);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point spritePos = getPosition();

	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);
	Point destPos = Point(x, y);
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centerPos - destPos;
	parent->setPosition(viewPos);

}

void Player::setTagPosition(const int x, const int y)
{
	
	Item::setTagPosition(x, y);
	setViewPointByPlayer();
}

void Player::setTiledMap(AdventureMapLayer* map)
{
	this->m_map = map;
}

void Player::setiNowCD(int cd)
{
	if (cd > m_iTotalCD)
		m_iNowCD = m_iTotalCD;
	else if (cd < 0)
		m_iNowCD = 0;
	else
		m_iNowCD = cd;
}

void Player::setiTotalCD(int cd)
{
	if (cd < 0)
		m_iTotalCD = 0;
	else
		m_iTotalCD = cd;
}

void Player::setiNowMp(int mp)
{
	if (mp > m_iTotalMp)
		m_iNowMp = m_iTotalMp;
	else if (mp < 0)
		m_iNowMp = 0;
	else
		m_iNowMp = mp;
}

void Player::setiTotalMp(int mp)
{
	if (mp < 0)
		m_iTotalMp = 0;
	else
		m_iTotalMp = mp;
}

Point Player::tileCoordForPosition(Point pos)
{
	int x = pos.x / ((m_map->getMap())->getTileSize().width);
	int y = ((m_map->getMap()->getMapSize().height * m_map->getMap()->getTileSize().height) - pos.y)
		/ ((m_map->getMap())->getTileSize().height);

	return Point(x, y);
}

void Player::setiNowSkillDuration(int duration)
{
	if (duration > m_iTotalSkillDuration)
		m_iNowSkillDuration = m_iTotalSkillDuration;
	else if (duration < 0)
		m_iNowSkillDuration = 0;
	else
		m_iNowSkillDuration = duration;
}

void Player::setiTotalSkillDuration(int duration)
{
	if (duration < 0)
		m_iTotalSkillDuration = 0;
	else
		m_iTotalSkillDuration = duration;
}

int Player::isPositiveOrNegative(int num)
{
	if (num > 0)
		return 1;
	else if (num < 0)
		return -1;
	else
		return 0;
}

void Player::setLongRange(LongRange* longRange)
{ 
	m_longRange = longRange; 
	m_longRange->setPosition( 0, -5);
	m_longRange->bindMap(m_map);
	this->addChild(m_longRange);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = [longRange,this](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		longRange->attack(pos);
		if (pos.x < 1024/2)//ÆÁÄ»Ò»°ë´óÐ¡
		{
			setRightToward();
		}
		else
		{
			setLeftToward();
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Player::setRightToward()
{
	if (this->getRightSide() == true)
	{
		this->setLeftSide(true);
		this->setRightSide(false);
		m_sprite->setFlipX(true);
	}
}

void Player::setLeftToward()
{
	if (this->getLeftSide() == true)
	{
		this->setLeftSide(false);
		this->setRightSide(true);
		m_sprite->setFlipX(false);
	}
}

std::vector<Bullet*> Player::getBullet()const
{
	std::vector<Bullet*> bullets;
	for (auto bullet : m_longRange->getBullet())
	{
		bullets.push_back(bullet);
	}
	return bullets;
}

void Player::hit(int damage)
{

}

void Player::getBulletFromWeapon()
{
	
}