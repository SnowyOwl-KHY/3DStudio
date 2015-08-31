#ifndef TEXTURE_H
#define TEXTURE_H

#include "StdAfx.h"
#include "gl/glut.h"  
#include "math.h"  
#include "gl/glaux.h" // GLaux库的头文件  
#pragma comment(lib, "glaux.lib")      // GLaux连接库  
#include <stdlib.h>
#include <vector>
#include "type.h"

class TexturePainter
{
private:
	vector<vertex3> vertexVect;
	vector<vertex3> normalVect;
	vector<vertex3> uvVect;
	GLuint textureNum;
	bool LoadT8(LPCWSTR filename, GLuint &texture);
	polygon mypolygon;   //用于绘画多面棱柱、多面棱锥的多边形面
	polygon tUpPolygon;
	polygon tDownPolygon;
	void DrawCircle(GLfloat r, GLfloat z, GLint, GLint, bool, int index);
	void DrawPolygon(GLint surfaceNum, GLfloat zdata, GLfloat radius, int index);

public:
	GLuint texture[100];  //贴图  
	GLUquadricObj *g_text;
	GLuint LoadTexture(LPCWSTR filename);
	TexturePainter();
	void DrawCube(GLfloat length, GLfloat width, GLfloat height, int index);
	void DrawSphere(GLfloat radius, GLint iSlices, GLint iStacks, int index);
	void DrawCylinder(GLfloat radius, GLfloat height, GLint iSlices, GLint iStacks, int index);
	void DrawPrismoid(GLint surfaceNum, GLfloat height, GLfloat radius, int index);
	void DrawCone(GLfloat base, GLfloat height, GLint iSlices, GLint iStacks, int index);
	void DrawTrustum(GLint surfaceNum, GLfloat height, GLfloat r, GLfloat scale, int index);
};

#endif