#pragma once

class MainScene;
class GameScene;
class StageScene_1;
#include "cocos2d.h"
#include "Global.h"
#include "BackGroundLayer.h"
#include "DialogLayer.h"
#include "ControlLayer.h"
#include "AttackLayer.h"
#include "DanmakuLayer.h"
#include "ObstacleLayer.h"
#include "MedicineLayer.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;


class GameScene : public Scene
{
public:
	bool init();
	void setEffectFlag(bool effectFlag);

protected:
	virtual void initGame() = 0;
	virtual void attackSchedule() = 0;
	virtual void danmakuSchedule() = 0;
	virtual void obstacleSchedule() = 0;
	virtual void medicineSchedule() = 0;
	virtual void Gameover() = 0;
	virtual void Victory() = 0;
	void GameLogic();
	void stageDanmaku(const unsigned char* level);
	void setSpeed(float speed);
	void setSlowMode();
	void checkBomb();
	void checkMedicinePower();
	void checkAttack(int health);
	void checkDanmaku(int health);
	void checkGraze();
	void checkGrazePower();
	void checkObstacle(int health);
	void checkMedicine(int health);
	void checkRestart();
	void Bomb();
	void update(float dt);

	Size visibleSize;
	Point origin;
	bool winFlag;
	bool effectFlag;
	bool playingFlag;
	int danmakuLevel;
	int obstacleLevel;
	int obstacleTime;
	int obstacleCount;
	int medicineTime;
	int process;
	int attackPower;
	int medicineRegain;
	int danmakuPower;
	int obstaclePower;
	int playerHealthMax;
	int enemyHealthMax;

	BackGroundLayer* bg;
	DialogLayer* dialog;
	ControlLayer* control;
	PlayerLayer* player;
	EnemyLayer* enemy;
	DanmakuLayer* danmaku;
	ObstacleLayer* obstacle;
	MedicineLayer* medicine;
	AttackLayer* attack;
};

#define OX2 0,0
#define OX5 0,0,0,0,0
#define OX8 OX5,0,0,0
#define OX10 OX5,OX5
#define OX12 OX10,OX2
#define OX14 OX10,OX2,0,0
#define OX16 OX8,OX8
#define OX18 OX10,OX8
#define OX20 OX10,OX10

//0<angle<=180 0<num<=16 0<=speed<16
#define NS(num,speed) (speed*16+(num-1))
#define NAS(num,angle,speed) angle,NS(num,speed)
#define PNAS(player,num,angle,speed) (player>0)?(player*2+179):(player*-2+211),angle,NS(num,speed)
#define BNAS(boss,num,angle,speed) (boss>0)?(boss*2+180):(boss*-2+212),angle,NS(num,speed)
#define SAP 255
#define SPAP(s_x,s_y,a_x,a_y,num,angle,speed) SAP,s_x+s_y*8,a_x+a_y*8,angle,NS(num,speed)
#define SAA 254
#define SPAA(s_x,s_y,a_angle,num,angle,speed) SAA,s_x+s_y*8,(a_angle>=0)?(a_angle):(a_angle*-1+90),angle,NS(num,speed)