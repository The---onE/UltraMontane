#include "EnemyLayer.h"

#define MOVE_ACTION 1

bool EnemyLayer::init()
{
#define EnemySize 0.16
#define EnemyPositionX visibleSize.width*7/8
#define EnemyPositionY visibleSize.height*3/6
#define HealthSizeY 0.032
#define HealthSizeX 0.5
#define HealthPositionX visibleSize.width
#define HealthPositionY visibleSize.height

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/enemy.plist", "sprites/enemy.png");

	health=1;
	healthMax=1;
	enemyFrameNum = 17;
	enemyAnimateSpeed = 0.15f;
	createEnemy("e_0/e_0.png");
	createHealth("enemyhealth.png");

	runUpward();
	this->scheduleUpdate();

	return true;
}

void EnemyLayer::createEnemy(std::string filename)
{
	Enemy = Sprite::createWithSpriteFrameName(filename);
	Animation *enemyAnimate = Animation::create();
	for (int i=0; i<enemyFrameNum; i++)
	{
		char name[32];
		sprintf(name, "e_0/e_0_0/e_0_0_%d.png", i);
		enemyAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	enemyAnimate->setDelayPerUnit(enemyAnimateSpeed);
	Enemy->runAction(RepeatForever::create(Animate::create(enemyAnimate)));

	Enemy->setPosition(Point(origin.x + EnemyPositionX, origin.y + EnemyPositionY));
	Enemy->setFlippedX(true);
	float ee = Enemy->getContentSize().height;
	SETSIZE(Enemy, EnemySize);
	this->addChild(Enemy);
}

void EnemyLayer::createHealth(std::string filename)
{
	Health = Sprite::createWithSpriteFrameName(filename);
	Health->setAnchorPoint(Point(1, 1));
	SETSIZE(Health, HealthSizeY);
	healthLength = visibleSize.width / Health->getContentSize().width * HealthSizeX;
	Health->setScaleX(healthLength * health / healthMax);
	Health->setPosition(Point(origin.x + HealthPositionX, origin.y + HealthPositionY));
	this->addChild(Health, -1);
}

bool EnemyLayer::changeHealth(int delta)
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

void EnemyLayer::runUpward()
{
	Enemy->stopActionByTag(MOVE_ACTION);
	ActionInterval* run = MoveBy::create(1, Point(0, 10));
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, 8);
	runs->setTag(MOVE_ACTION);
	Enemy->runAction(runs);
}

void EnemyLayer::runDownward()
{
	Enemy->stopActionByTag(MOVE_ACTION);
	ActionInterval* run = MoveBy::create(1, Point(0, -10));
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, 8);
	runs->setTag(MOVE_ACTION);
	Enemy->runAction(runs);
}

Point EnemyLayer::getEnemyPosition()
{
	return Enemy->getPosition();
}

Rect EnemyLayer::getEnemyRect()
{
	return Enemy->getBoundingBox();
}

void EnemyLayer::setHealth(int health)
{
	this->health = health;
}

void EnemyLayer::setHealthMax(int healthMax)
{
	this->healthMax = healthMax;
}

void EnemyLayer::update(float dt)
{
	float y = Enemy->getPositionY();
	if (y < 0.3*visibleSize.height)
	{
		Enemy->setPositionY(0.3000001*visibleSize.height);
		runUpward();
	}
	else if (y > 0.7*visibleSize.height)
	{
		Enemy->setPositionY(0.6999999*visibleSize.height);
		runDownward();
	}
}