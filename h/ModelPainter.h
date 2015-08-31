#ifndef MODELPAINTER_H_
#define MODELPAINTER_H_
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "gl/glut.h"
#include "type.h"

#define pi 3.141592653589

using namespace std;

class ModelPainter
{
	private:
		polygon mypolygon;   //用于绘画多面棱柱、多面棱锥的多边形面
		polygon tUpPolygon;
		polygon tDownPolygon;
		void DrawCircle(GLfloat r,GLfloat z, GLint,GLint,bool);
		void DrawPolygon(GLint surfaceNum, GLfloat zdata,GLfloat radius);
	public:
		void DrawCube(GLfloat length,GLfloat width,GLfloat height);
		void DrawSphere(GLfloat radius, GLint iSlices, GLint iStacks);
		void DrawCylinder(GLfloat radius,GLfloat height,GLint iSlices, GLint iStacks);
		void DrawPrismoid( GLint surfaceNum, GLfloat height,GLfloat radius);
		void DrawCone(GLfloat base,GLfloat height,GLint iSlices,GLint iStacks);
		void DrawTrustum(GLint surfaceNum, GLfloat height,GLfloat r,GLfloat scale);
};

#endif