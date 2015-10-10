#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
USING_NS_CC;

class DialogLayer : public Layer
{
public:
	CREATE_FUNC(DialogLayer);
	bool isFinish();

protected:
	bool init();
	void onEnter();
	void createBox(std::string filename);
	void deleteBox();
	void createSkip(std::string filenameN, std::string filenameS);
	void Skip();
	void loadText(std::string filename);
	void loadStage(int stageIndex);
	const char* loadDialog(int dialogIndex);
	void createDialogSprite();
	void createCharacter();
	void showDialog();
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* text;
	tinyxml2::XMLElement* stage;
	tinyxml2::XMLElement* dialog;
	std::string character;
	std::string playerFolder;
	std::string enemyFolder;
	int stageProcess;
	int dialogProcess;
	int dialogCount;
	Sprite* box;
	LabelTTF* dialogSprite;
	std::string dialogText;
	Sprite* playerPicture;
	Sprite* enemyPicture;
	bool FinishFlag;
	Size visibleSize;
	Point origin;
};

