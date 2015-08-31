#ifndef _LIGHT_H
#define _LIGHT_H

#include <Windows.h>
#include "gl/glut.h"
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Light {
public:
	Light();
	~Light();

	void enable();
	void disable();
	virtual void show() = 0;

public:
	GLfloat position[4];//光源位置
	GLfloat Model_Ambient[4]; //全局环境光
	static bool flag[2];

protected:
	static GLenum lightId[2];
	int id;
};

class SpotLight : public Light {
public:
	SpotLight();
	~SpotLight();

	virtual void show();

public:
	GLfloat ambient[4];//环境光成分
	GLfloat diffuse[4];//漫反射成分
	GLfloat specular[4];//镜面光成分
};

class DirectLight : public SpotLight {
public:
	DirectLight();
	~DirectLight();

	virtual void show();

public:
	GLfloat cutoff;
	GLfloat direction[4];
	GLfloat exponent;
};


#endif
