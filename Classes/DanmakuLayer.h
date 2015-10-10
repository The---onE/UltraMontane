#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class DanmakuLayer :public Layer
{
public:
	CREATE_FUNC(DanmakuLayer);
	bool checkGrazeNum();
	void clearDanmaku();
	void P2P(Point Aim, Point Source, int num, int angelDeg,int speed);
	int checkCollision(Point playerPosition);
	bool checkGraze(Point playerPosition);

protected:
	bool init();
	void createDanmaku(std::string filename, Point& pos);
	void run2P(Point& pos, int d, int speed);
	void update(float dt);

	std::shared_ptr<Vector<Sprite*>> danmakuArray;
	Sprite* Bullet;
	int grazeNum;
	float hitDistance;
	float grazeDistance;
	int powerUpNum;
	Size visibleSize;
	Point origin;
};

