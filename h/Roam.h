#pragma once
#include "StdAfx.h"
#include "Display.h"
class Roam
{
public:
	Roam(Display& dmanager);
	~Roam();

	void rotateCenter(CPoint nowPt, CPoint prePt);
	void rotateEye(CPoint nowPt, CPoint prePt);
	void ahead(bool collisionTest = true);
	void back(bool collisionTest = true);
	void left(bool collisionTest = true);
	void right(bool collisionTest = true);
	void up(bool collisionTest = true);
	void down(bool collisionTest = true);
	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();
	void reset();
	void switchRotateState();
	void rotate();
	void flash();
	void flashRotate();
	void enableMaze();
	void disableMaze();

	double eyeX, eyeY, eyeZ;// 在gluLookAt中使用的3个向量
	double centerX, centerY, centerZ;
	double upX, upY, upZ;

	Display& display;

private:
	void changeAngle(CPoint nowPt, CPoint prePt, bool eyeFlag);
	void turn(int direct);
	void mazeVictoryTest();
	void turnToMaze();

	double tVerticalAng, tHorizonAng, tRadius, tAngInc; // 水平方向、垂直方向的角、半径
	static const double PI;
	static int stepSize;
	int rotateCount;
	bool flashFlag;

	double oldEyeX, oldEyeY, oldEyeZ;
	double oldCenterX, oldCenterY, oldCenterZ;
	void setEyeAndCenter(double eX, double eY, double eZ, double cX, double cY, double cZ);
};

