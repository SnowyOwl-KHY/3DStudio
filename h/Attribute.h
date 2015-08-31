#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H
#include "stdafx.h" 
enum Type {
	CUBE,		//³¤·½Ìå
	SPHERE,		//ÇòÌå
	CYLINDER,	//Ô²Öù
	PRISMOID,	//ÀâÖù
	CONE,		//Ô²×¶
	TRUSTUM,	//ÀâÌ¨
	IMPORT,		//µ¼Èë
	UNKNOWN
};

enum MaterialType {
	BRASS,		//»ÆÍ­
	BRONZE,		//ÇàÍ­
	GOLD,			//½ð
	WAX,			//°×À¯
	SILVER,			//Òø
	EMERALD,		//ôä´ä
	OBSIDIAN,		//ºÚê×Ê¯
	BLACKPLASTIC,	//ºÚËÜÁÏ
	BLACKRUBBER		//ºÚÏð½º
};

struct Color {
	int r;
	int g;
	int b;
	float a;

	Color() {
		r = 255;
		g = 255;
		b = 255;
		a = 1;
	}
	Color(int r, int g, int b, float a = 1) {
		if (r > 255) r = 255;
		if (r < 0) r = 0;
		if (g > 255) g = 255;
		if (g < 0) g = 0;
		if (b > 255) b = 255;
		if (b < 0) b = 0;
		if (a > 1) a = 1;
		if (a < 0) a = 0;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

struct Translate {
	double x;
	double y;
	double z;

	Translate() {
		x = 0;
		y = 0;
		z = 0;
	}
	Translate(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Rotate {
	double angle;
	double x;
	double y;
	double z;

	Rotate() {
		angle = 0;
		x = 0;
		y = 0;
		z = 1;
	}
	Rotate(double angle, double x, double y, double z) {
		this->angle = angle;
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Parameter {
};

struct CubeParameter : Parameter {
	GLfloat length;
	GLfloat width;
	GLfloat height;

	CubeParameter() {
		length = 100;
		width = 100;
		height = 100;
	}
	CubeParameter(GLfloat length, GLfloat width, GLfloat height) {
		this->length = length;
		this->width = width;
		this->height = height;
	}
};

struct SphereParameter : Parameter {
	GLfloat radius;
	GLint iSlices;
	GLint iStacks;

	SphereParameter() {
		radius = 50;
		iSlices = 50;
		iStacks = 50;
	}
	SphereParameter(GLfloat radius, GLint iSlices, GLint iStacks) {
		this->radius = radius;
		this->iSlices = iSlices;
		this->iStacks = iStacks;
	}
};

struct CylinderParameter : Parameter {
	GLfloat radius;
	GLfloat height;
	GLint iSlices;
	GLint iStacks;

	CylinderParameter() {
		radius = 50;
		height = 100;
		iSlices = 50;
		iStacks = 50;
	}
	CylinderParameter(GLfloat radius, GLfloat height, GLint iSlices, GLint iStacks) {
		this->radius = radius;
		this->height = height;
		this->iSlices = iSlices;
		this->iStacks = iStacks;
	}
};

struct PrismoidParameter : Parameter {
	GLint surfaceNum;
	GLfloat height;
	GLfloat radius;

	PrismoidParameter() {
		surfaceNum = 6;
		height = 100;
		radius = 50;
	}
	PrismoidParameter(GLint surfaceNum, GLfloat height, GLfloat radius) {
		this->surfaceNum = surfaceNum;
		this->height = height;
		this->radius = radius;
	}
};

struct ConeParameter : Parameter {
	GLfloat base;
	GLfloat height;
	GLint iSlices;
	GLint iStacks;

	ConeParameter() {
		base = 50;
		height = 100;
		iSlices = 50;
		iStacks = 50;
	}
	ConeParameter(GLfloat base, GLfloat height, GLint iSlices, GLint iStacks) {
		this->base = base;
		this->height = height;
		this->iSlices = iSlices;
		this->iStacks = iStacks;
	}
};

struct TrustumParameter : Parameter {
	GLint surfaceNum;
	GLfloat height;
	GLfloat radius;
	GLfloat scale;

	TrustumParameter() {
		surfaceNum = 6;
		height = 100;
		radius = 50;
		scale = 0.5;
	}
	TrustumParameter(GLint surfaceNum, GLfloat height, GLfloat radius, GLfloat scale) {
		this->surfaceNum = surfaceNum;
		this->height = height;
		this->radius = radius;
		this->scale = scale;
	}
};

struct ImportParameter : Parameter {
	CString fileName;

	ImportParameter() {
	}
	ImportParameter(CString fileName) {
		this->fileName = fileName;
	}
};



#endif
