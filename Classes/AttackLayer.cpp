#include "AttackLayer.h"

bool AttackLayer::init()
{
#define attackItemSize 0.16
#define attackItemPositionX visibleSize.width*0.55
#define BulletSize 0.032
#define bombItemSize 0.16
#define bombItemPositionX visibleSize.width*0.8
#define bombLableFontSize 48
#define bombLablePositionX visibleSize.width*0.8
#define normalBulletAngel 10
#define normalBulletSpeed 120
#define slowBulletAngel 3
#define slowBulletSpeed 160

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/bullet.plist", "sprites/bullet.png");

	bulletArray = std::make_shared<Vector<Sprite*>>();

	powerLevel = 3;
	bombFlag = false;
	fireFlag = true;
	slowFlag = false;

	maxBulletHeight = visibleSize.height*0.18;

	createAttackButton("attack.png", "attack.png");
	createBombButton("bomb_n.png", "bomb_s.png");
	createBombLable();

	this->scheduleUpdate();

	return true;
}

void AttackLayer::onEnter()
{
	Layer::onEnter();
	/*//////////////////////////////////////////////////*/
	KEYBOARD_LISTENER(AttackLayer);
	/*//////////////////////////////////////////////////*/
}

/*//////////////////////////////////////////////////*/
void AttackLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_X:
		Bomb();
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		changeAttack();
		break;
	default:
		break;
	}
}

void AttackLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	default:
		break;
	}
}
/*//////////////////////////////////////////////////*/

void AttackLayer::createAttackButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* attackItem = MenuItemImage::create();
	attackItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	attackItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	attackItem->setCallback(CC_CALLBACK_0(AttackLayer::changeAttack, this));

	SETSIZE(attackItem, attackItemSize);
	attackItem->setAnchorPoint(Point(0, 0));
	attackItem->setPosition(Point(origin.x + attackItemPositionX, origin.y));
	Menu* attack = Menu::create(attackItem, NULL);
	attack->setPosition(Point::ZERO);
	this->addChild(attack);
}

void AttackLayer::createBullet(std::string filename, Point& pos)
{
	Bullet = Sprite::createWithSpriteFrameName(filename);
	bulletArray->pushBack(Bullet);
	SETSIZE(Bullet, BulletSize);
	Bullet->setPosition(pos);
	this->addChild(Bullet);
}


void AttackLayer::createBombButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* bombItem = MenuItemImage::create();
	bombItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	bombItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	bombItem->setCallback(CC_CALLBACK_0(AttackLayer::Bomb, this));

	SETSIZE(bombItem, bombItemSize);
	bombItem->setAnchorPoint(Point(1, 0));
	bombItem->setPosition(Point(origin.x + bombItemPositionX, origin.y));
	Menu* bomb = Menu::create(bombItem, NULL);
	bomb->setPosition(Point::ZERO);
	this->addChild(bomb);
}

void AttackLayer::createBombLable()
{
	this->removeChild(bombLable);
	char lable[8];
	sprintf(lable, "*%d", powerLevel);
	bombLable = LabelTTF::create(lable, "Arial", bombLableFontSize);
	bombLable->setAnchorPoint(Point(0, 0));
	bombLable->setPosition(Point(origin.x + bombLablePositionX, origin.y));
	this->addChild(bombLable);
}

void AttackLayer::powerUp()
{
	powerLevel++;
	createBombLable();
}

void AttackLayer::powerDown()
{
	powerLevel--;
	createBombLable();
}

void AttackLayer::run2P(Point& pos, int d, int speed)
{
	ActionInterval* run = MoveBy::create(d, pos);
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, speed*10);
	Bullet->runAction(runs);
	int angle = atan2(pos.y, -pos.x)*180/3.14;
	Bullet->setRotation(angle);
}

void AttackLayer::P2P(Point Aim, Point Source, int num, int angelDeg,int speed)
{
	Point Temp;
	float angelRad = (float)angelDeg/180*3.14 / num;
	int d = Aim.getDistance(Source);
	float halfangle = angelRad / 2;
	if (num%2 == 1)
	{
		halfangle = 0;
		createBullet("sb_0.png", Source);
		Point Temp = Point(Aim.x - Source.x, Aim.y - Source.y);
		run2P(Temp, d, speed);
	}
	for (int i=1; i<=(num/2); i++)
	{
		createBullet("sb_0.png", Source);
		float angel = angelRad * i -halfangle;
		int x = (Aim.x - Source.x)*cos(angel) - (Aim.y - Source.y)*sin(angel);
		int y = (Aim.y - Source.y)*cos(angel) + (Aim.x - Source.x)*sin(angel);
		Temp = Point(x, y);
		run2P(Temp, d, speed);

		createBullet("sb_0.png", Source);
		angel = -angelRad * i +halfangle;
		x = (Aim.x - Source.x)*cos(angel) - (Aim.y - Source.y)*sin(angel);
		y = (Aim.y - Source.y)*cos(angel) + (Aim.x - Source.x)*sin(angel);
		Temp = Point(x, y);
		run2P(Temp, d, speed);
	}
}

void AttackLayer::changeAttack()
{
	fireFlag = !fireFlag;
}

void AttackLayer::bulletAttack(Point p, Point e)
{
	if (fireFlag)
	{
		if (!slowFlag)
		{
			int delta = p.y - e.y;
			if (delta > maxBulletHeight)
			{
				e.setPoint(e.x, p.y - maxBulletHeight);
			}
			else if (delta < -maxBulletHeight)
			{
				e.setPoint(e.x, p.y + maxBulletHeight);
			}
			P2P(e, p, powerLevel, normalBulletAngel, normalBulletSpeed);
		}
		else
		{
			P2P(e, p, powerLevel, slowBulletAngel, slowBulletSpeed);
		}
	}
}

int AttackLayer::checkCollision(Rect enemtRect)
{
	int j = 0;
	for (int i=bulletArray->size()-1; i>=0; --i)
	{
		Sprite* bullet = (Sprite*)bulletArray->at(i);
		Point p = bullet->getPosition();

		if (enemtRect.containsPoint(p))
		{
			bulletArray->eraseObject(bullet);
			removeChild(bullet);
			j++;
		}
	}
	return j;
}

void AttackLayer::Bomb()
{
	if (!bombFlag)
	{
		if (powerLevel > 1)
		{
			bombFlag = true;
			powerDown();
		}
	}
}

bool AttackLayer::isBomb()
{
	return bombFlag;
}

void AttackLayer::setBombFlag(bool bombFlag)
{
	this->bombFlag = bombFlag;
}

void AttackLayer::setSlowFlag(bool flag)
{
	slowFlag = flag;
}

void AttackLayer::update(float dt)
{
 	for (int i=bulletArray->size()-1; i>=0; --i)
 	{
 		Sprite* bullet = (Sprite*)bulletArray->at(i);
 		Point position = bullet->getPosition();
 		if (position.x<0 || position.y<0 || position.x>visibleSize.width || position.y>visibleSize.height)
 		{
 			bulletArray->eraseObject(bullet);
 			removeChild(bullet);
 		}
 	}
}