#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "GameScene.h"
USING_NS_CC;

class StageScene_1 : public GameScene
{
public:
	CREATE_FUNC(StageScene_1);
protected:
	bool init();
	void initGame();
	void attackSchedule();
	void danmakuSchedule();
	void obstacleSchedule();
	void medicineSchedule();
	void runDanmaku(float dt);
	void runObstacle(float dt);
	void runMedicine(float dt);
	void runAttack(float dt);
	void Gameover();
	void Victory();

	const static unsigned char stage1[];
	const static unsigned char stage1_f[];
};

