#pragma once
#include "StdAfx.h"
class Material
{
public:
	Material();
	~Material();

	void show();
	static void enable();
	static void disable();

	void brass();//黄铜
	void bronze();//青铜
	void gold();//金
	void wax();//白蜡
	void silver();//银
	void emerald();//翡翠
	void obsidian();//黑曜石
	void blackPlastic();//黑塑料
	void blackRubber();//黑橡胶
	void setMaterial(int index);
	void reset();
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;//镜面反射系数

private:
	static bool flag;

};

