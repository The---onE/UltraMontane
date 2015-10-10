#pragma once

#define SETSIZE(SPRITE,SIZE) (SPRITE)->setScale(visibleSize.height/(SPRITE)->getContentSize().height*(SIZE))

#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
						  void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
								 keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this);\
								 keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this);\
								 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
