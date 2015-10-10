#include "MainScene.h"
#include "StageScene_1.h"

bool MainScene::init()
{
	Scene::init();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	LabelTTF* startLable = LabelTTF::create("Start Game", "Arial", 48);
	MenuItemLabel* startGame = MenuItemLabel::create(startLable, CC_CALLBACK_0(MainScene::StartGame, this));

	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	LabelTTF* playLable = LabelTTF::create("Play BGM", "Arial", 48);
	MenuItemLabel* playBGM = MenuItemLabel::create(playLable);
	LabelTTF* stopLable = LabelTTF::create("Stop BGM", "Arial", 48);
	MenuItemLabel* stopBGM = MenuItemLabel::create(stopLable);
	MenuItemToggle* bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MainScene::PlayStopBGM, this), playBGM, stopBGM, NULL);

	effectFlag = false;
	LabelTTF* openEffectLable = LabelTTF::create("Open Effect", "Arial", 48);
	MenuItemLabel* openEffect = MenuItemLabel::create(openEffectLable);
	LabelTTF* closeEffectLable = LabelTTF::create("Close Effect", "Arial", 48);
	MenuItemLabel* closeEffect = MenuItemLabel::create(closeEffectLable);
	MenuItemToggle* effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MainScene::OpenCloseEffect, this), openEffect, closeEffect, NULL);

	LabelTTF* quitLable = LabelTTF::create("Quit Game", "Arial", 48);
	MenuItemLabel* quitGame = MenuItemLabel::create(quitLable, CC_CALLBACK_0(MainScene::QuitGame, this));

	Menu* mainMenu = Menu::create(startGame, bgm, effect, quitGame, NULL);
	mainMenu->alignItemsVerticallyWithPadding(20);
	this->addChild(mainMenu, 1000);

	createBackGround("sprites/main.jpg");

	return true;
}

void MainScene::StartGame()
{
	StageScene_1* game = StageScene_1::create();
	game->setEffectFlag(effectFlag);
	Director::getInstance()->replaceScene(game);
}

void MainScene::PlayStopBGM()
{
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying())
	{
		audio->stopBackgroundMusic();
	}
	else
	{
		audio->playBackgroundMusic("musics/bgm.mp3");
	}
}

void MainScene::OpenCloseEffect()
{
	effectFlag = !effectFlag;
}

void MainScene::QuitGame()
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

void MainScene::createBackGround(std::string filename)
{
	Sprite* Bg = Sprite::create(filename);
	Bg->setScaleX(visibleSize.width/Bg->getContentSize().width);
	Bg->setScaleY(visibleSize.height/Bg->getContentSize().height);
	Bg->setAnchorPoint(Point(0, 0));
	Bg->setPosition(Point(0, 0));
	this->addChild(Bg, -1000);
}