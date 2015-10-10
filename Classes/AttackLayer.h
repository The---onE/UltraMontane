#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class AttackLayer : public Layer
{
public:
	CREATE_FUNC(AttackLayer);
	void bulletAttack(Point p, Point e);
	int checkCollision(Rect enemtRect);
	void powerUp();
	void setSlowFlag(bool flag);
	bool isBomb();
	void setBombFlag(bool bombFlag);

protected:
	bool init();
	void onEnter();
	void createAttackButton(std::string filenameN, std::string filenameS);
	void createBullet(std::string filename, Point& pos);
	void createBombButton(std::string filenameN, std::string filenameS);
	void createBombLable();
	void run2P(Point& pos, int d, int speed);
	void P2P(Point Aim, Point Source, int num, int angelDeg,int speed);
	void changeAttack();
	void powerDown();
	void Bomb();
	void update(float dt);
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	std::shared_ptr<Vector<Sprite*>> bulletArray;
	Sprite* Bullet;
	LabelTTF* bombLable;
	int powerLevel;
	bool fireFlag;
	bool slowFlag;
	bool bombFlag;
	float maxBulletHeight;
	Size visibleSize;
	Point origin;
};
