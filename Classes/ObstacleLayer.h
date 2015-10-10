#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class ObstacleLayer : public Layer
{
public:
	CREATE_FUNC(ObstacleLayer);
	void randomObstacle();
	int checkCollision(Point playerPosition);
	void clearObstacle();
	void setSpeed(float speed);

protected:
	bool init();
	void createObstacleRect(std::string filename, float y);
	void update(float dt);

	std::shared_ptr<Vector<Sprite*>> obstacleRectArray;
	Sprite* Obstacle;
	float speed;
	float hitRectX;
	float hitRectY;
	Size visibleSize;
	Point origin;
};

