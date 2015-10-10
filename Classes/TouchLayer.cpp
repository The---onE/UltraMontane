#include "TouchLayer.h"

#define MOVE_ACTION 1

bool TouchLayer::init()
{
#define downwardSize 0.32
#define upwardSize 0.32
#define upwardPositionY downrect.size.height + visibleSize.height * 0.1

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	normolSpeed = 50;
	slowSpeed = 20;
	speed = normolSpeed;
	moveFlag = false;
	slowFlag = false;

	createDownwareButton("downward.png");
	createUpwardButton("upward.png");

	return true;
}

void TouchLayer::onEnter()
{
	Layer::onEnter();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	parent = (PlayerLayer*)(this->getParent());

	/*//////////////////////////////////////////////////*/
	KEYBOARD_LISTENER(TouchLayer);
	/*//////////////////////////////////////////////////*/
}

/*//////////////////////////////////////////////////*/
void TouchLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!moveFlag)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_SHIFT:
			SpeedDown();
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			runUpward();
			parent->upwardAnimate();
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			runDownward();
			parent->downwardAnimate();
			break;
		default:
			break;
		}
	}
	else
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_SHIFT:
			SpeedDown();
			break;
		default:
			break;
		}
	}
}

void TouchLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SHIFT:
		SpeedUp();
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player->stopActionByTag(MOVE_ACTION);
		moveFlag = false;
		parent->standAnimete();
		break;
	default:
		break;
	}
}
/*//////////////////////////////////////////////////*/

void TouchLayer::createDownwareButton(std::string filename)
{
	downward = Sprite::createWithSpriteFrameName(filename);
	SETSIZE(downward, downwardSize);
	downward->setAnchorPoint(Point(0, 0));
	downward->setPosition(Point(origin.x, origin.y));
	this->addChild(downward);
	downrect = downward->getBoundingBox();
}

void TouchLayer::createUpwardButton(std::string filename)
{
	upward = Sprite::createWithSpriteFrameName(filename);
	SETSIZE(upward, upwardSize);
	upward->setAnchorPoint(Point(0, 0));
	upward->setPosition(Point(origin.x, origin.y + upwardPositionY));
	this->addChild(upward);
	uprect = upward->getBoundingBox();
}

void TouchLayer::runUpward()
{
	ActionInterval* run = MoveBy::create(1, Point(0, 10));
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, speed);
	runs->setTag(MOVE_ACTION);
	player->runAction(runs);
	moveFlag = true;
}

void TouchLayer::runDownward()
{
	ActionInterval* run = MoveBy::create(1, Point(0, -10));
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, speed);
	runs->setTag(MOVE_ACTION);
	player->runAction(runs);
	moveFlag = true;
}

void TouchLayer::SpeedDown()
{
	if (!slowFlag)
	{
		slowFlag = true;
		speed = slowSpeed;
		parent->setSlowMode(true);
		if (moveFlag)
		{
			Speed* runs = (Speed*)(player->getActionByTag(MOVE_ACTION));
			runs->setSpeed(speed);
		}
	}
}

void TouchLayer::SpeedUp()
{
	if (slowFlag)
	{
		slowFlag = false;
		speed = normolSpeed;
		parent->setSlowMode(false);
		if (moveFlag)
		{
			Speed* runs = (Speed*)(player->getActionByTag(MOVE_ACTION));
			runs->setSpeed(speed);
		}
	}
}

void TouchLayer::setPlayer(Sprite* player)
{
	this->player = player;
}

bool TouchLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Point touchPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	if (!moveFlag)
	{
		if (uprect.containsPoint(touchPoint))
		{
			runUpward();
			parent->upwardAnimate();
		}
		else if (downrect.containsPoint(touchPoint))
		{
			runDownward();
			parent->downwardAnimate();
		}
		else if(touchPoint.x > 0.5*visibleSize.width && touchPoint.y > 0.16*visibleSize.height)
		{
			SpeedDown();
		}
	}
	else if(touchPoint.x > 0.5*visibleSize.width && touchPoint.y > 0.16*visibleSize.height)
	{
		SpeedDown();
	}

	return true;
}

void TouchLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void TouchLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	Point startPoint = pTouch->getStartLocation();
	if (moveFlag && (uprect.containsPoint(startPoint) || downrect.containsPoint(startPoint)))
	{
		player->stopActionByTag(MOVE_ACTION);
		moveFlag = false;
		parent->standAnimete();
	}
	else if(startPoint.x > 0.5*visibleSize.width && startPoint.y > 0.16*visibleSize.height)
	{
		SpeedUp();
	}
}