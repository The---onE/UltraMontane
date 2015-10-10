#include "DanmakuLayer.h"

bool DanmakuLayer::init()
{
#define BulletSize 0.032

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	danmakuArray = std::make_shared<Vector<Sprite*>>();
	grazeNum = 0;

	hitDistance = visibleSize.height*0.02;
	grazeDistance = visibleSize.height*0.05;

	powerUpNum = 20;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/bullet.plist", "sprites/bullet.png");

	this->scheduleUpdate();

	return true;
}

void DanmakuLayer::P2P(Point Aim, Point Source, int num, int angelDeg, int speed)
{
	Point Temp;
	int type = (int)(CCRANDOM_0_1()*1000) % 8;
	char name[32];
	sprintf(name, "bb_%d.png", type);
	float angelRad = (float)angelDeg/180*3.14 / num;
	int d = Aim.getDistance(Source);
	float halfangle = angelRad / 2;
 	if (num%2 == 1)
 	{
 		halfangle = 0;
		createDanmaku(name, Source);
		Point Temp = Point(Aim.x - Source.x, Aim.y - Source.y);
		run2P(Temp, d, speed);
 	}
 	for (int i=1; i<=(num/2); i++)
	{
		createDanmaku(name, Source);
 		float angel = angelRad * i -halfangle;
 		int x = (Aim.x - Source.x)*cos(angel) - (Aim.y - Source.y)*sin(angel);
 		int y = (Aim.y - Source.y)*cos(angel) + (Aim.x - Source.x)*sin(angel);
		Temp = Point(x, y);
		run2P(Temp, d, speed);

		createDanmaku(name, Source);
		angel = -angelRad * i +halfangle;
		x = (Aim.x - Source.x)*cos(angel) - (Aim.y - Source.y)*sin(angel);
		y = (Aim.y - Source.y)*cos(angel) + (Aim.x - Source.x)*sin(angel);
		Temp = Point(x, y);
		run2P(Temp, d, speed);
 	}
}

void DanmakuLayer::createDanmaku(std::string filename, Point& pos)
{
	Bullet = Sprite::createWithSpriteFrameName(filename);
	danmakuArray->pushBack(Bullet);
	SETSIZE(Bullet, BulletSize);
	Bullet->setPosition(pos);
	this->addChild(Bullet);
}

void DanmakuLayer::run2P(Point& pos, int d, int speed)
{
	ActionInterval* run = MoveBy::create(d, pos);
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, speed*10);
	Bullet->runAction(runs);
	int angle = atan2(pos.y, -pos.x)*180/3.14;
	Bullet->setRotation(angle);
}

int DanmakuLayer::checkCollision(Point playerPosition)
{
	int j = 0;
	for (int i=danmakuArray->size()-1; i>=0; --i)
	{
		Sprite* bullet = (Sprite*)danmakuArray->at(i);
		Point position = bullet->getPosition();

		if (position.getDistance(playerPosition) < hitDistance)
		{
			danmakuArray->eraseObject(bullet);
			removeChild(bullet);
			j++;
		}
	}
	return j;
}

bool DanmakuLayer::checkGraze(Point playerPosition)
{
	bool flag = false;
	for (int i=danmakuArray->size()-1; i>=0; --i)
	{
		Sprite* bullet = (Sprite*)danmakuArray->at(i);
		Point position = bullet->getPosition();
		float distance = position.getDistance(playerPosition);

		if ((position.x < playerPosition.x) && 
			(distance < grazeDistance) && 
			(distance > hitDistance))
		{
			if (!bullet->isFlippedY())
			{
				grazeNum++;
				bullet->setFlippedY(true);
				flag = true;
			}
		}
	}
	return flag;
}

bool DanmakuLayer::checkGrazeNum()
{
 	if (grazeNum >= powerUpNum)
 	{
 		grazeNum = 0;
 		return true;
 	}
 	return false;
}

void DanmakuLayer::clearDanmaku()
{
	for (int i=danmakuArray->size()-1; i>=0; --i)
	{
		Sprite* bullet = (Sprite*)danmakuArray->at(i);
		danmakuArray->eraseObject(bullet);
		removeChild(bullet);
	}
}

void DanmakuLayer::update(float dt)
{
	for (int i=danmakuArray->size()-1; i>=0; --i)
	{
		Sprite* bullet = (Sprite*)danmakuArray->at(i);
		Point position = bullet->getPosition();
		if (position.x<0 || position.y<0 || position.x>visibleSize.width || position.y>visibleSize.height)
		{
			danmakuArray->eraseObject(bullet);
			removeChild(bullet);
		}
	}
}