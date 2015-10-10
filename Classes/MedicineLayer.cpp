#include "MedicineLayer.h"
#include <stdlib.h>

bool MedicineLayer::init()
{
#define MedicineSize 0.12

	medicineArray = std::make_shared<Vector<Sprite*>>();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/obstacle.plist", "sprites/obstacle.png");

	power = 0;
	speed = 2;
	powerUpNum = 8;
	medicineDistance = visibleSize.height*0.08;
	this->scheduleUpdate();

	return true;
}

void MedicineLayer::createMedicine(std::string filename, float y)
{
	Medicine = Sprite::createWithSpriteFrameName(filename);
	SETSIZE(Medicine, MedicineSize);
	Medicine->setPosition(Point(origin.x + visibleSize.width + Medicine->getContentSize().width * Medicine->getScaleY()/2, origin.y + y));
	medicineArray->pushBack(Medicine);
	this->addChild(Medicine);
}

void MedicineLayer::randomMedicine()
{
	float y = visibleSize.height * CCRANDOM_0_1();
	this->createMedicine("o_1.png", y);
}

int MedicineLayer::checkCollision(Point playerPosition)
{
	int j = 0;
	for (int i=medicineArray->size()-1; i>=0; --i)
	{
		Sprite* obstacle = (Sprite*)medicineArray->at(i);
		Point position = obstacle->getPosition();

		if (position.getDistance(playerPosition) < medicineDistance)
		{
			power++;
			medicineArray->eraseObject(obstacle);
			removeChild(obstacle);
			j++;
		}
	}
	return j;
}

bool MedicineLayer::checkPower()
{
	if (power >= powerUpNum)
	{
		power = 0;
		return true;
	}
	return false;
}

void MedicineLayer::setSpeed(float speed)
{
	this->speed = speed;
}

void MedicineLayer::update(float dt)
{
	for (int i=medicineArray->size()-1; i>=0; --i)
	{
		Sprite* medicine = (Sprite*)medicineArray->at(i);
		float x = medicine->getPositionX();
		if (x < -medicine->getContentSize().width * Medicine->getScaleY()/2)
		{
			medicineArray->eraseObject(medicine);
			this->removeChild(medicine);
		}
		else
		{
			medicine->setPositionX(x - speed);
		}
	}
}
