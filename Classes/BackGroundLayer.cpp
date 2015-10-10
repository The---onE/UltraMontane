#include "BackGroundLayer.h"

// on "init" you need to initialize your instance
bool BackGroundLayer::init()
{
    Layer::init();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	createBackGround("sprites/bg.png");

	speed = 2;

	this->scheduleUpdate();
    
    return true;
}

void BackGroundLayer::createBackGround(std::string filename)
{
	Bg = Sprite::create(filename);
	Bg->setAnchorPoint(Point(0, 0));
	SETSIZE(Bg, 1);
	Bg->setPosition(Point(0, 0));
	this->addChild(Bg);

	tempBg = Sprite::create(filename);
	tempBg->setAnchorPoint(Point(1, 0));
	SETSIZE(tempBg, 1);
	tempBg->setPosition(Point(visibleSize.width, 0));
	tempBg->setVisible(false);
	this->addChild(tempBg, 0);

	BgWidth = Bg->getContentSize().width * Bg->getScaleY();
}

void BackGroundLayer::setSpeed(float speed)
{
	this->speed = speed;
}

void BackGroundLayer::update(float dt)
{
	float x = Bg->getPositionX() - speed;
	float y = Bg->getPositionY();
	if (x < visibleSize.width - BgWidth)
	{
		x = visibleSize.width;
		tempBg->setVisible(true);
		tempBg->setPosition(Point(x, 0));
	}
	Bg->setPosition(Point(x, y));
	if (tempBg->isVisible())
	{
		if (x < 0)
		{
			tempBg->setVisible(false);
		}
		tempBg->setPosition(Point(x, y));
	}
}