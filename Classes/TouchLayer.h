#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "PlayerLayer.h"
USING_NS_CC;

class PlayerLayer;

class TouchLayer : public Layer
{
public:
	CREATE_FUNC(TouchLayer);
	void setPlayer(Sprite* player);

protected:
	bool init();
	void onEnter();
	void createDownwareButton(std::string filename);
	void createUpwardButton(std::string filename);
	void runUpward();
	void runDownward();
	void SpeedDown();
	void SpeedUp();
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	Sprite* player;
	Sprite* upward;
	Sprite* downward;
	PlayerLayer* parent;
	Rect uprect;
	Rect downrect;
	int speed;
	int normolSpeed;
	int slowSpeed;
	bool moveFlag;
	bool slowFlag;
	Size visibleSize;
	Point origin;
};

