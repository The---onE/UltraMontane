#include "PlayerLayer.h"

#define STAND_ANIMATE 1
#define UPWARD_ANIMATE 2
#define DOWNWARD_ANIMATE 3

bool PlayerLayer::init()
{
#define PlayerSize 0.12
#define PlayerPositionX visibleSize.width*1/4
#define PlayerPositionY visibleSize.height*3/6
#define PositionPointSize 0.04
#define HealthSizeX 0.5
#define HealthSizeY 0.032
#define HealthPositionY visibleSize.height

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/player.plist", "sprites/player.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/bullet.plist", "sprites/bullet.png");

	health=1;
	healthMax=1;
	playerStandFrameNum = 14;
	playerStandAnimateSpeed = 0.15f;
	playerUpwardFrameNum = 5;
	playerUpwardAnimateSpeed = 0.15f;
	playerDownwardFrameNum = 5;
	playerDownwardAnimateSpeed = 0.15f;
	createPlayer("p_0/p_0.png", "pp.png");
	createHealth("selfhealth.png");

	slowFlag = false;

	this->scheduleUpdate();

	touch = TouchLayer::create();
	touch->setPlayer(Player);
	this->addChild(touch);

	return true;
}

void PlayerLayer::createPlayer(std::string filename, std::string pointname)
{
	Player = Sprite::createWithSpriteFrameName(filename);
	standAnimete();
	Player->setPosition(Point(origin.x + PlayerPositionX, origin.y + PlayerPositionY));
	SETSIZE(Player, PlayerSize);
	this->addChild(Player);
	PositionPoint = Sprite::createWithSpriteFrameName(pointname);
	PositionPoint->setPosition(Player->getPosition());
	SETSIZE(PositionPoint, PositionPointSize);
	this->addChild(PositionPoint);
	PositionPoint->setVisible(false);
}

void PlayerLayer::standAnimete()
{
	Player->stopActionByTag(UPWARD_ANIMATE);
	Player->stopActionByTag(DOWNWARD_ANIMATE);
	Animation *playerAnimate = Animation::create();
	for (int i=0; i<playerStandFrameNum; i++)
	{
		char name[32];
		sprintf(name, "p_0/p_0_0/p_0_0_%d.png", i);
		playerAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	playerAnimate->setDelayPerUnit(playerStandAnimateSpeed);
	RepeatForever* animate = RepeatForever::create(Animate::create(playerAnimate));
	animate->setTag(STAND_ANIMATE);
	Player->runAction(animate);
}

void PlayerLayer::upwardAnimate()
{
	Player->stopActionByTag(STAND_ANIMATE);
	Player->stopActionByTag(DOWNWARD_ANIMATE);
	Animation *playerAnimate = Animation::create();
	for (int i=0; i<playerUpwardFrameNum; i++)
	{
		char name[32];
		sprintf(name, "p_0/p_0_1/p_0_1_%d.png", i);
		playerAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	playerAnimate->setDelayPerUnit(playerUpwardAnimateSpeed);
	RepeatForever* animate = RepeatForever::create(Animate::create(playerAnimate));
	animate->setTag(UPWARD_ANIMATE);
	Player->runAction(animate);
}

void PlayerLayer::downwardAnimate()
{
	Player->stopActionByTag(STAND_ANIMATE);
	Player->stopActionByTag(UPWARD_ANIMATE);
	Animation *playerAnimate = Animation::create();
	for (int i=0; i<playerDownwardFrameNum; i++)
	{
		char name[32];
		sprintf(name, "p_0/p_0_2/p_0_2_%d.png", i);
		playerAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	playerAnimate->setDelayPerUnit(playerDownwardAnimateSpeed);
	RepeatForever* animate = RepeatForever::create(Animate::create(playerAnimate));
	animate->setTag(DOWNWARD_ANIMATE);
	Player->runAction(animate);
}

void PlayerLayer::createHealth(std::string filename)
{
	Health = Sprite::createWithSpriteFrameName(filename);
	Health->setAnchorPoint(Point(0, 1));
	SETSIZE(Health, HealthSizeY);
	healthLength = visibleSize.width / Health->getContentSize().width * HealthSizeX;
	Health->setScaleX(healthLength * health / healthMax);
	Health->setPosition(Point(origin.x, origin.y + HealthPositionY));
	this->addChild(Health, -1);
}

bool PlayerLayer::changeHealth(int delta)
{
	bool negative = false;
	health += delta;
	if (health < 0)
	{
		health = 0;
		negative = true;
	}
	if (health > healthMax)
	{
		health = healthMax;
	}
	Health->setScaleX(healthLength * health / healthMax); 
	return negative;
}

void PlayerLayer::setSlowMode(bool flag)
{

	slowFlag = flag;
	PositionPoint->setVisible(flag);
}

bool PlayerLayer::isSlow()
{
	return slowFlag;
}

void PlayerLayer::setHealth(int health)
{
	this->health = health;
}

void PlayerLayer::setHealthMax(int healthMax)
{
	this->healthMax = healthMax;
}

Point PlayerLayer::getPlayerPosition()
{
	return Player->getPosition();
}

Rect PlayerLayer::getPlayerRect()
{
	return Player->getBoundingBox();
}

void PlayerLayer::update(float dt)
{
	PositionPoint->setPosition(Player->getPosition());
	Point position = Player->getPosition();
	if (position.x < 0)
	{
		Player->setPositionX(0);
	}
	else if (position.x >visibleSize.width)
	{
		Player->setPositionX(visibleSize.width);
	}
	if (position.y < 0)
	{
		Player->setPositionY(0);
	}
	else if (position.y > visibleSize.height)
	{
		Player->setPositionY(visibleSize.height);
	}
}
