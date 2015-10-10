#include "ObstacleLayer.h"

bool ObstacleLayer::init()
{
#define ObstacleSize 0.16

	obstacleRectArray = std::make_shared<Vector<Sprite*>>();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/obstacle.plist", "sprites/obstacle.png");

	hitRectX = visibleSize.height*0.008;
	hitRectY = visibleSize.height*0.008;
	speed = 2;
	this->scheduleUpdate();

	return true;
}

void ObstacleLayer::createObstacleRect(std::string filename, float y)
{
	Obstacle = Sprite::createWithSpriteFrameName(filename);
	SETSIZE(Obstacle, ObstacleSize);
	Obstacle->setAnchorPoint(Point(0, 0.5));
	Obstacle->setPosition(Point(origin.x + visibleSize.width, origin.y + y));
	obstacleRectArray->pushBack(Obstacle);
	this->addChild(Obstacle);
}

void ObstacleLayer::randomObstacle()
{
	float y = visibleSize.height * CCRANDOM_0_1();
	this->createObstacleRect("o_0.png", y);
}

int ObstacleLayer::checkCollision(Point playerPosition)
{
	int j = 0;
	Rect playerRect = Rect(playerPosition.x - hitRectX/2, playerPosition.y - hitRectY/2, hitRectX, hitRectY);
	for (int i=obstacleRectArray->size()-1; i>=0; --i)
	{
		Sprite* obstacle = (Sprite*)obstacleRectArray->at(i);
		Rect obRect = obstacle->getBoundingBox();
		if (obRect.intersectsRect(playerRect))
		{
			obstacleRectArray->eraseObject(obstacle);
			removeChild(obstacle);
			j++;
		}
	}
	return j;
}

void ObstacleLayer::clearObstacle()
{
	for (int i=obstacleRectArray->size()-1; i>=0; --i)
	{
		Sprite* obstacle = (Sprite*)obstacleRectArray->at(i);
		obstacleRectArray->eraseObject(obstacle);
		removeChild(obstacle);
	}
}

void ObstacleLayer::setSpeed(float speed)
{
	this->speed = speed;
}

void ObstacleLayer::update(float dt)
{
 	for (int i=obstacleRectArray->size()-1; i>=0; --i)
 	{
 		Sprite* obstacle = (Sprite*)obstacleRectArray->at(i);
 		float x = obstacle->getPositionX();
 		if (x < -obstacle->getContentSize().width * Obstacle->getScaleY())
 		{
 			obstacleRectArray->eraseObject(obstacle);
 			this->removeChild(obstacle);
 		}
 		else
 		{
 			obstacle->setPositionX(x - speed);
 		}
 	}
}