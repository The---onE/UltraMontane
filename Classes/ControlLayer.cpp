#include "ControlLayer.h"

bool ControlLayer::init()
{
#define closeItemSize 0.1
#define closeItemPositionX visibleSize.width
#define pauseItemSize 0.1
#define pauseItemPositionX visibleSize.width
#define pauseItemPositionY visibleSize.height/2
#define restartItemSize 0.1
#define restartItemPositionX visibleSize.width
#define restartItemPositionY visibleSize.height*0.16

	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	createCloseButton("close_n.png", "close_s.png");
	createPauseButton("pause_n.png", "pause_s.png");
	createRestartButton("restart_n.png", "restart_s.png");

	pauseFlag = false;
	restartFlag = false;

	return true;
}

void ControlLayer::onEnter()
{
	Layer::onEnter();
	
	/*//////////////////////////////////////////////////*/
	KEYBOARD_LISTENER(ControlLayer);
	/*//////////////////////////////////////////////////*/
}

/*//////////////////////////////////////////////////*/
void ControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
  	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_R:
		restartGame();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		pauseGame();
		break;
	case EventKeyboard::KeyCode::KEY_F4:
		quitGame();
		break;
	default:
		break;
	}
}

void ControlLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	default:
		break;
	}
}
/*//////////////////////////////////////////////////*/

void ControlLayer::createCloseButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* closeItem = MenuItemImage::create();
	closeItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	closeItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	closeItem->setCallback(CC_CALLBACK_0(ControlLayer::quitGame, this));

	SETSIZE(closeItem, closeItemSize);
	closeItem->setAnchorPoint(Point(1, 0));
	closeItem->setPosition(Point(origin.x + closeItemPositionX, origin.y));
	Menu* pMenu = Menu::create(closeItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}

void ControlLayer::createPauseButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* pauseItem = MenuItemImage::create();
	pauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	pauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	pauseItem->setCallback(CC_CALLBACK_0(ControlLayer::pauseGame, this));

	SETSIZE(pauseItem, pauseItemSize);
	pauseItem->setAnchorPoint(Point(1, 0.5));
	pauseItem->setPosition(Point(origin.x + pauseItemPositionX, origin.y + pauseItemPositionY));
	Menu* pMenu = Menu::create(pauseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}

void ControlLayer::createRestartButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* restartItem = MenuItemImage::create();
	restartItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	restartItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	restartItem->setCallback(CC_CALLBACK_0(ControlLayer::restartGame, this));

	SETSIZE(restartItem, 0.1);
	restartItem->setAnchorPoint(Point(1, 0));
	restartItem->setPosition(Point(origin.x + restartItemPositionX, origin.y + restartItemPositionY));
	Menu* pMenu = Menu::create(restartItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}


void ControlLayer::pauseGame()
{
	if (pauseFlag)
	{
		Director::getInstance()->resume();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		pauseFlag = false;
	}
	else
	{
		Director::getInstance()->pause();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		pauseFlag = true;
	}
}

void ControlLayer::quitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void ControlLayer::restartGame()
{
	restartFlag = true;
}

bool ControlLayer::isRestart()
{
	return restartFlag;
}