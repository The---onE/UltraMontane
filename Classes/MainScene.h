#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class MainScene : public Scene
{
public:
	CREATE_FUNC(MainScene);
	bool init();

protected:
	void StartGame();
	void PlayStopBGM();
	void OpenCloseEffect();
	void QuitGame();
	void createBackGround(std::string filename);

	Size visibleSize;
	Point origin;
	bool effectFlag;
};

