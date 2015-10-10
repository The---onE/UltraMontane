#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class MedicineLayer : public Layer
{
public:
	CREATE_FUNC(MedicineLayer);
	int checkCollision(Point playerPosition);
	bool checkPower();
	void randomMedicine();
	void setSpeed(float speed);

protected:
	bool init();
	void createMedicine(std::string filename, float y);
	void update(float dt);

	std::shared_ptr<Vector<Sprite*>> medicineArray;
	Sprite* Medicine;
	float speed;
	int power;
	int powerUpNum;
	float medicineDistance;
	Size visibleSize;
	Point origin;
};

