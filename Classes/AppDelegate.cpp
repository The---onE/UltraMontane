#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* pDirector = Director::getInstance();
    EGLView* pEGLView = EGLView::getInstance();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/item.plist", "sprites/item.png");

	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("musics/bgm.mp3");
	audio->preloadEffect("musics/hurt.wav");
	audio->preloadEffect("musics/extend.wav");
	audio->preloadEffect("musics/bomb.wav");
	audio->preloadEffect("musics/graze.wav");

    // create a scene. it's an autorelease object
    MainScene *pScene = MainScene::create();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
