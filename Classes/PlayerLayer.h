#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "TouchLayer.h"
USING_NS_CC;

class TouchLayer;

class PlayerLayer : public Layer
{
public:
	CREATE_FUNC(PlayerLayer);
	bool changeHealth(int delta);
	void standAnimete();
	void upwardAnimate();
	void downwardAnimate();
	bool isSlow();
	void setSlowMode(bool flag);
	void setHealth(int health);
	void setHealthMax(int healthMax);
	Point getPlayerPosition();
	Rect getPlayerRect();

protected:
	bool init();
	void createPlayer(std::string filename, std::string pointname);
	void createHealth(std::string filename);
	void update(float dt);

	TouchLayer* touch;
	Sprite* Player;
	Sprite* PositionPoint;
	Sprite* Health;
	float healthLength;
	bool slowFlag;
	int health;
	int healthMax;
	int playerStandFrameNum;
	float playerStandAnimateSpeed;
	int playerUpwardFrameNum;
	float playerUpwardAnimateSpeed;
	int playerDownwardFrameNum;
	float playerDownwardAnimateSpeed;
	Size visibleSize;
	Point origin;
};