#include "stdafx.h"
#include "Roam.h"

const double Roam::PI = 3.1415926535897;
int Roam::stepSize = 5;

Roam::Roam(Display& dmanager) : display(dmanager) {
	reset();
}


Roam::~Roam() {
}

void Roam::rotateCenter(CPoint nowPt, CPoint prePt) {
	changeAngle(nowPt, prePt, false);
	//¶¯center
	centerX = eyeX - tRadius * cos(tVerticalAng) * cos(tHorizonAng);
	centerY = eyeY - tRadius * sin(tVerticalAng);
	centerZ = eyeZ - tRadius * cos(tVerticalAng) * sin(tHorizonAng);
}

void Roam::rotateEye(CPoint nowPt, CPoint prePt) {
	if (display.isInMaze()) return; //ÃÔ¹¬×´Ì¬½ûÖ¹
	changeAngle(nowPt, prePt, true);
	//¶¯eye
	eyeX = tRadius * cos(tVerticalAng) * cos(tHorizonAng) + centerX;
	eyeY = tRadius * sin(tVerticalAng) + centerY;
	eyeZ = tRadius * cos(tVerticalAng) * sin(tHorizonAng) + centerZ;
}

void Roam::changeAngle(CPoint nowPt, CPoint prePt, bool eyeFlag) {
	double tDx = nowPt.x - prePt.x;
	double tDy = nowPt.y - prePt.y;
	if (eyeFlag == false) {
		tDx = -tDx;
		tDy = -tDy;
		tAngInc = PI / 180;
	}
	else {
		tAngInc = PI / 90;
	}
	double tDis = sqrt(tDx*tDx + tDy*tDy);
	if (tDx > 0.) {
		tHorizonAng += tAngInc * tDx / tDis;
		if (tHorizonAng < 0.) { tHorizonAng += 2 * PI; }
		if (tHorizonAng > 2 * PI) { tHorizonAng -= 2 * PI; }
	}
	else if (tDx < 0.) {
		tHorizonAng += tAngInc * tDx / tDis;
		if (tHorizonAng < 0.) { tHorizonAng += 2 * PI; }
		if (tHorizonAng > 2 * PI) { tHorizonAng -= 2 * PI; }
	}
	if (tDy > 0.) {
		tVerticalAng = tVerticalAng + tAngInc * tDy / tDis;
		if (tVerticalAng > PI / 2) { tVerticalAng = PI / 2; }
	}
	else if (tDy < 0.) {
		tVerticalAng = tVerticalAng + tAngInc * tDy / tDis;
		if (tVerticalAng < -PI / 2) { tVerticalAng = -PI / 2; }
	}
}

void Roam::ahead(bool collisionTest) {
	double direct[3] = { (eyeX - centerX) / tRadius, 0, (eyeZ - centerZ) / tRadius };
	if (collisionTest == false || display.test(eyeX - stepSize * direct[0], eyeY, eyeZ)) {
		eyeX -= stepSize * direct[0];
		centerX -= stepSize * direct[0];
	}
	if (collisionTest == false || display.test(eyeX, eyeY - stepSize * direct[1], eyeZ)) {
		eyeY -= stepSize * direct[1];
		centerY -= stepSize * direct[1];
	}
	if (collisionTest == false || display.test(eyeX, eyeY, eyeZ - stepSize * direct[2])) {
		eyeZ -= stepSize * direct[2];
		centerZ -= stepSize * direct[2];
	}
	mazeVictoryTest();
}

void Roam::back(bool collisionTest) {
	double direct[3] = { (eyeX - centerX) / tRadius, 0, (eyeZ - centerZ) / tRadius };
	if (collisionTest == false || display.test(eyeX + stepSize * direct[0], eyeY, eyeZ)) {
		eyeX += stepSize * direct[0];
		centerX += stepSize * direct[0];
	}
	if (collisionTest == false || display.test(eyeX, eyeY + stepSize * direct[1], eyeZ)) {
		eyeY += stepSize * direct[1];
		centerY += stepSize * direct[1];
	}
	if (collisionTest == false || display.test(eyeX, eyeY, eyeZ + stepSize * direct[2])) {
		eyeZ += stepSize * direct[2];
		centerZ += stepSize * direct[2];
	}
	mazeVictoryTest();
}

void Roam::left(bool collisionTest) {
	double direct[3] = { (eyeX - centerX) / tRadius, (eyeY - centerY) / tRadius, (eyeZ - centerZ) / tRadius };
	//a X b, a = direct, b = up
	double rightDirect[3] = { direct[1] * upZ - upY * direct[2], direct[2] * upX - upZ * direct[0], direct[0] * upY - upX * direct[1] };
	double rightDirectLength = sqrt(rightDirect[0] * rightDirect[0] + rightDirect[1] * rightDirect[1] + rightDirect[2] * rightDirect[2]);
	double rightUnitedDirect[3] = { rightDirect[0] / rightDirectLength, rightDirect[1] / rightDirectLength, rightDirect[2] / rightDirectLength };

	if (collisionTest == false || display.test(eyeX + stepSize * rightUnitedDirect[0], eyeY, eyeZ)) {
		eyeX += stepSize * rightUnitedDirect[0];
		centerX += stepSize * rightUnitedDirect[0];
	}
	if (collisionTest == false || display.test(eyeX, eyeY + stepSize * rightUnitedDirect[1], eyeZ)) {
		eyeY += stepSize * rightUnitedDirect[1];
		centerY += stepSize * rightUnitedDirect[1];
	}
	if (collisionTest == false || display.test(eyeX, eyeY, eyeZ + stepSize * rightUnitedDirect[2])) {
		eyeZ += stepSize * rightUnitedDirect[2];
		centerZ += stepSize * rightUnitedDirect[2];
	}
	mazeVictoryTest();
}

void Roam::right(bool collisionTest) {
	double direct[3] = { (eyeX - centerX) / tRadius, (eyeY - centerY) / tRadius, (eyeZ - centerZ) / tRadius };
	//a X b, a = direct, b = up
	double rightDirect[3] = { direct[1] * upZ - upY * direct[2], direct[2] * upX - upZ * direct[0], direct[0] * upY - upX * direct[1] };
	double rightDirectLength = sqrt(rightDirect[0] * rightDirect[0] + rightDirect[1] * rightDirect[1] + rightDirect[2] * rightDirect[2]);
	double rightUnitedDirect[3] = { rightDirect[0] / rightDirectLength, rightDirect[1] / rightDirectLength, rightDirect[2] / rightDirectLength };

	if (collisionTest == false || display.test(eyeX - stepSize * rightUnitedDirect[0], eyeY, eyeZ)) {
		eyeX -= stepSize * rightUnitedDirect[0];
		centerX -= stepSize * rightUnitedDirect[0];
	}
	if (collisionTest == false || display.test(eyeX, eyeY - stepSize * rightUnitedDirect[1], eyeZ)) {
		eyeY -= stepSize * rightUnitedDirect[1];
		centerY -= stepSize * rightUnitedDirect[1];
	}
	if (collisionTest == false || display.test(eyeX, eyeY, eyeZ - stepSize * rightUnitedDirect[2])) {
		eyeZ -= stepSize * rightUnitedDirect[2];
		centerZ -= stepSize * rightUnitedDirect[2];
	}
	mazeVictoryTest();
}

void Roam::mazeVictoryTest() {
	if (display.isInMaze() == false) return;
	if (eyeX < Display::mazeLength * Display::mazeCubeSize / 2 && eyeX > -Display::mazeLength * Display::mazeCubeSize / 2
		&& eyeZ < Display::mazeLength * Display::mazeCubeSize / 2 && eyeZ > -Display::mazeLength * Display::mazeCubeSize / 2) return;
	AfxMessageBox(_T("Congratulations!"));
	disableMaze();
}

void Roam::enableMaze() {
	oldEyeX = eyeX;
	oldEyeY = eyeY;
	oldEyeZ = eyeZ;
	oldCenterX = centerX;
	oldCenterY = centerY;
	oldCenterZ = centerZ;
	stepSize = 1;
	turnToMaze();
	display.enableMaze();
}

void Roam::disableMaze() {
	stepSize = 5;
	display.disableMaze();
	setEyeAndCenter(oldEyeX, oldEyeY, oldEyeZ, oldCenterX, oldCenterY, oldCenterZ);
}

void Roam::turnToMaze() {
	eyeX = 0.;
	eyeY = 5.;
	eyeZ = 10.;
	centerX = 0.;
	centerY = 5.;
	centerZ = 0.;
	upX = 0.;
	upY = 1.0;
	upZ = 0.;
	tRadius = sqrt(eyeX * eyeX + eyeY * eyeY + eyeZ * eyeZ);

	tVerticalAng = asin((eyeY - centerY) / tRadius);
	tHorizonAng = acos((eyeX - centerX) / tRadius);
	rotateCount = 0;
	flashFlag = false;
}

void Roam::up(bool collisionTest) {
	if (display.isInMaze()) return;//ÃÔ¹¬×´Ì¬½û·É
	double upDirect[3] = { upX, upY, upZ };
	if (collisionTest == false || display.test(eyeX + stepSize * upDirect[0], eyeY, eyeZ)) {
		eyeX += stepSize * upDirect[0];
		centerX += stepSize * upDirect[0];
	}
	if (collisionTest == false || display.test(eyeX, eyeY + stepSize * upDirect[1], eyeZ)) {
		eyeY += stepSize * upDirect[1];
		centerY += stepSize * upDirect[1];
	}
	if (collisionTest == false || display.test(eyeX, eyeY, eyeZ + stepSize * upDirect[2])) {
		eyeZ += stepSize * upDirect[2];
		centerZ += stepSize * upDirect[2];
	}
}

void Roam::down(bool collisionTest) {
	if (display.isInMaze()) return;//ÃÔ¹¬×´Ì¬½û·É
	double upDirect[3] = { upX, upY, upZ };
	if (collisionTest == false || display.test(eyeX - stepSize * upDirect[0], eyeY, eyeZ)) {
		eyeX -= stepSize * upDirect[0];
		centerX -= stepSize * upDirect[0];
	}
	if (collisionTest == false || display.test(eyeX, eyeY - stepSize * upDirect[1], eyeZ)) {
		eyeY -= stepSize * upDirect[1];
		centerY -= stepSize * upDirect[1];
	}
	if (collisionTest == false || display.test(eyeX, eyeY, eyeZ - stepSize * upDirect[2])) {
		eyeZ -= stepSize * upDirect[2];
		centerZ -= stepSize * upDirect[2];
	}
}

void Roam::turnLeft() {
	turn(0);
}

void Roam::turnRight() {
	turn(1);
}

void Roam::turnUp() {
	turn(2);
}

void Roam::turnDown() {
	turn(3);
}

void Roam::turn(int direct) {
	int dX[4] = { 1, -1, 0, 0 };
	int dY[4] = { 0, 0, 1, -1 };
	CPoint nowPt(5 * dX[direct], 5 * dY[direct]);
	CPoint prePt(0, 0);
	rotateCenter(nowPt, prePt);
}

void Roam::reset() {
	eyeX = 0.;
	eyeY = 400.;
	eyeZ = 400.;
	centerX = 0.;
	centerY = 0.;
	centerZ = 0.;
	upX = 0.;
	upY = 1.0;
	upZ = 0.;
	tRadius = sqrt(eyeX * eyeX + eyeY * eyeY + eyeZ * eyeZ);

	tVerticalAng = asin((eyeY - centerY) / tRadius);
	tHorizonAng = acos((eyeX - centerX) / tRadius);
	rotateCount = 0;
	flashFlag = false;
}

void Roam::rotate() {
	tHorizonAng += PI / 90;

	eyeX = tRadius * cos(tVerticalAng) * cos(tHorizonAng) + centerX;
	eyeY = tRadius * sin(tVerticalAng) + centerY;
	eyeZ = tRadius * cos(tVerticalAng) * sin(tHorizonAng) + centerZ;
}

void Roam::flashRotate() {
	if (flashFlag) {
		tHorizonAng += PI / 60;

		eyeX = tRadius * cos(tVerticalAng) * cos(tHorizonAng) + centerX;
		eyeY = tRadius * sin(tVerticalAng) + centerY;
		eyeZ = tRadius * cos(tVerticalAng) * sin(tHorizonAng) + centerZ;
		if (++rotateCount >= 120) {
			rotateCount = 0;
			flashFlag = false;
			setEyeAndCenter(oldEyeX, oldEyeY, oldEyeZ, oldCenterX, oldCenterY, oldCenterZ);
		}
	}
}

void Roam::flash() {
	oldEyeX = eyeX;
	oldEyeY = eyeY;
	oldEyeZ = eyeZ;
	oldCenterX = centerX;
	oldCenterY = centerY;
	oldCenterZ = centerZ;
	reset();
	flashFlag = true;
}

void Roam::setEyeAndCenter(double eX, double eY, double eZ, double cX, double cY, double cZ) {
	eyeX = eX;
	eyeY = eY;
	eyeZ = eZ;
	centerX = cX;
	centerY = cY;
	centerZ = cZ;
	tRadius = sqrt(eyeX * eyeX + eyeY * eyeY + eyeZ * eyeZ);

	tVerticalAng = asin((eyeY - centerY) / tRadius);
	tHorizonAng = acos((eyeX - centerX) / tRadius);
	rotateCount = 0;
	flashFlag = false;
}
