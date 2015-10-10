#include "GameScene.h"
#include "MainScene.h"

bool GameScene::init()
{
	Scene::init();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	bg = NULL;
	dialog = NULL;
	control = NULL;
	player = NULL;
	enemy  = NULL;
	danmaku = NULL;
	obstacle = NULL;
	medicine = NULL;
	attack = NULL;

	winFlag = false;
	effectFlag = false;
	playingFlag = false;

	srand(time(NULL));
	this->scheduleUpdate();
	return true;
}

void GameScene::setEffectFlag(bool effectFlag)
{
	this->effectFlag = effectFlag;
}

void GameScene::GameLogic()
{
	attackSchedule();
 	danmakuSchedule();
	obstacleSchedule();
	medicineSchedule();
}

void GameScene::setSpeed(float speed)
{
	if (bg)
		bg->setSpeed(speed);
	if (obstacle)
		obstacle->setSpeed(speed);
	if (medicine)
		medicine->setSpeed(speed);
}

void GameScene::setSlowMode()
{
	if (attack && player)
		attack->setSlowFlag(player->isSlow());
}

void GameScene::stageDanmaku(const unsigned char* level)
{
	if (!danmaku)
		return;
	unsigned char flag = level[process];
	if (!flag){process++;return;}
	else
	{
		if (flag <= 180)
		{
			int angle = flag;
			process++;
			unsigned char numspeed = level[process];
			process++;
			int num = numspeed % 16 + 1;
			int speed = numspeed / 16 * 5;
			danmaku->P2P(player->getPlayerPosition(), enemy->getEnemyPosition(), num, angle, speed);
		}
		else if (SAP == flag)
		{
			process++;
			unsigned char s = level[process];
			process++;
			unsigned char a = level[process];
			process++;
			int s_x = s%8;
			int s_y = s/8;
			int a_x = a%8;
			int a_y = a/8;
			int angle = level[process];
			process++;
			unsigned char numspeed = level[process];
			process++;
			int num = numspeed % 16 + 1;
			int speed = numspeed / 16 * 5;
			danmaku->P2P(Point(visibleSize.width/8*a_x, visibleSize.height/32*a_y), Point(visibleSize.width/8*s_x, visibleSize.height/32*s_y), num, angle, speed);
		}
		else if (SAA == flag)
		{
			process++;
			unsigned char s = level[process];
			process++;
			int an = level[process];
			process++;
			if (an > 90)
			{
				an -= 90;
				an = -an;
			}
			float anRad = (float)an/180*3.14;

			int s_x_a = (s%8)*visibleSize.width/8;
			int s_y_a = (s/8)*visibleSize.height/32;

			int a_x_a = (-1000)*cos(anRad) + s_x_a;
			int a_y_a = (-1000)*sin(anRad) + s_y_a;

			int angle = level[process];
			process++;
			unsigned char numspeed = level[process];
			process++;
			int num = numspeed % 16 + 1;
			int speed = numspeed / 16 * 5;
			danmaku->P2P(Point(a_x_a, a_y_a), Point(s_x_a, s_y_a), num, angle, speed);
		}
		else
		{
			flag -= 180;
			if (flag % 2)
			{
				int playeroffset = flag / 2 + 1;
				if (playeroffset > 16)
				{
					playeroffset -= 16;
					playeroffset = -playeroffset;
				}
				process++;
				int angle = level[process];
				process++;
				unsigned char numspeed = level[process];
				process++;
				int num = numspeed % 16 + 1;
				int speed = numspeed / 16 * 5;
				danmaku->P2P(Point(player->getPlayerPosition().x, player->getPlayerPosition().y+visibleSize.height/32*playeroffset), enemy->getEnemyPosition(), num, angle, speed);
			}
			else
			{
				int bossoffset = flag / 2;
				if (bossoffset > 16)
				{
					bossoffset -= 16;
					bossoffset = -bossoffset;
				}
				process++;
				int angle = level[process];
				process++;
				unsigned char numspeed = level[process];
				process++;
				int num = numspeed % 16 + 1;
				int speed = numspeed / 16 * 5;
				danmaku->P2P(player->getPlayerPosition(), Point(enemy->getEnemyPosition().x, enemy->getEnemyPosition().y+visibleSize.height/32*bossoffset), num, angle, speed);
			}
		}
	}
}

void GameScene::checkBomb()
{
	if (attack)
	{
		if (attack->isBomb())
		{
			Bomb();
			attack->setBombFlag(false);
		}
	}
}

void GameScene::checkAttack(int health)
{
	if (attack && enemy)
	{
		int num;
		if (num = attack->checkCollision(enemy->getEnemyRect()))
		{
			if (enemy->changeHealth(health*num) && winFlag==false)
			{
				Victory();
			}
		}
	}
}

void GameScene::checkMedicine(int health)
{
	if (medicine && player)
	{
		int num;
		if (num = medicine->checkCollision(player->getPlayerPosition()))
		{
			if (!winFlag)
			{
				player->changeHealth(health*num); 
				if (effectFlag)
					SimpleAudioEngine::getInstance()->playEffect("musics/extend.wav");
			}
		}
	}
}

void GameScene::checkMedicinePower()
{
	if (medicine && attack)
	{
		if (medicine->checkPower())
		{
			attack->powerUp();
		}
	}
}

void GameScene::checkDanmaku(int health)
{
	if (danmaku && player)
	{
		int num;
		if (num = danmaku->checkCollision(player->getPlayerPosition()))
		{
			if (player->changeHealth(health*num) && winFlag==false)
			{
				Gameover();
			}
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/hurt.wav");
		}
	}
}

void GameScene::checkGraze()
{
	if (danmaku && player)
	{
		if (danmaku->checkGraze(player->getPlayerPosition()))
		{
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/graze.wav");
		}
	}
}

void GameScene::checkGrazePower()
{
	if (danmaku && attack)
	{
		if (danmaku->checkGrazeNum())
		{
			attack->powerUp();
		}
	}
}

void GameScene::checkObstacle(int health)
{
	if (obstacle && player)
	{
		int num;
		if (num = obstacle->checkCollision(player->getPlayerPosition()))
		{
			if (player->changeHealth(health*num) && winFlag==false)
			{
				Gameover();
			}
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/hurt.wav");
		}
	}
}

void GameScene::checkRestart()
{
	if (control)
	{
		if (control->isRestart())
		{
			MainScene* pScene = MainScene::create();
			Director::getInstance()->replaceScene(pScene);
		}
	}
}

void GameScene::Bomb()
{
	if (danmaku)
		danmaku->clearDanmaku();
	if (obstacle)
		obstacle->clearObstacle();
		if (effectFlag)
			SimpleAudioEngine::getInstance()->playEffect("musics/bomb.wav");
}

void GameScene::update(float dt)
{
	checkRestart();
	if (playingFlag)
	{
		checkBomb();
		checkAttack(attackPower);
		checkMedicine(medicineRegain);
		checkMedicinePower();
		checkDanmaku(danmakuPower);
		checkGraze();
		checkGrazePower();
		checkObstacle(obstaclePower);

		setSlowMode();
	}
	else
	{
		if (dialog->isFinish())
		{
			playingFlag = true;
			this->removeChild(dialog);
			initGame();
		}
	}
}