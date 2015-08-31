#include "StdAfx.h"
#include "Material.h"

bool Material::flag;

Material::Material(){
	reset();
}


Material::~Material(){
}

void Material::enable() {
	flag = true;
}

void Material::disable() {
	flag = false;
}

void Material::show() {
	if (flag) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		if (shininess > 0) {
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		}
		else {
			float black[] = { 0, 0, 0, 0 };
			glMaterialfv(GL_FRONT, GL_SPECULAR, black);
			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);
		}
	}
}

GLfloat MaterialTable[9][13] = {
	{//»ÆÍ­
		0.329412, 0.223529, 0.027451, 1.000000,
		0.780392, 0.568627, 0.113725, 1.000000,
		0.992157, 0.941176, 0.807843, 1.000000,
		27.897400
	},
	{//ÇàÍ­
		0.212500, 0.127500, 0.054000, 1.000000,
		0.714000, 0.428400, 0.181440, 1.000000,
		0.393548, 0.271906, 0.166721, 1.000000,
		25.600000
	},
	{//½ð
		0.247250, 0.199500, 0.074500, 1.000000,
		0.751640, 0.606480, 0.226480, 1.000000,
		0.628281, 0.555802, 0.366065, 1.000000,
		51.200001
	},
	{//°×À¯
		0.105882, 0.058824, 0.113725, 1.000000,
		0.427451, 0.470588, 0.541176, 1.000000,
		0.333333, 0.333333, 0.521569, 1.000000,
		9.846150
	},
	{//Òø
		0.192250, 0.192250, 0.192250, 1.000000,
		0.507540, 0.507540, 0.507540, 1.000000,
		0.508273, 0.508273, 0.508273, 1.000000,
		51.200001
	},
	{//ôä´ä
		0.021500, 0.174500, 0.021500, 0.550000,
		0.075680, 0.614240, 0.075680, 0.550000,
		0.633000, 0.727811, 0.633000, 0.550000,
		76.800003
	},
	{//ºÚê×Ê¯
		0.053750, 0.050000, 0.066250, 0.820000,
		0.182750, 0.170000, 0.225250, 0.820000,
		0.332741, 0.328634, 0.346435, 0.820000,
		38.400002
	},
	{//ºÚËÜÁÏ
		0.000000, 0.000000, 0.000000, 1.000000,
		0.010000, 0.010000, 0.010000, 1.000000,
		0.500000, 0.500000, 0.500000, 1.000000,
		32.000000
	},
	{//ºÚÏð½º
		0.020000, 0.020000, 0.020000, 1.000000,
		0.010000, 0.010000, 0.010000, 1.000000,
		0.400000, 0.400000, 0.400000, 1.000000,
		10.000000
	}
};

void Material::brass() {//»ÆÍ­
	setMaterial(0);
}
void Material::bronze() {//ÇàÍ­
	setMaterial(1);
}
void Material::gold() {//½ð
	setMaterial(2);
}
void Material::wax() {//°×À¯
	setMaterial(3);
}
void Material::silver() {//Òø
	setMaterial(4);
}
void Material::emerald() {//ôä´ä
	setMaterial(5);
}
void Material::obsidian() {//ºÚê×Ê¯
	setMaterial(6);
}
void Material::blackPlastic() {//ºÚËÜÁÏ
	setMaterial(7);
}
void Material::blackRubber() {//ºÚÏð½º
	setMaterial(8);
}

void Material::setMaterial(int index) {
	if (index < 0 || index > 8) {
		reset();
		return;
	}
	ambient[0] = MaterialTable[index][0];
	ambient[1] = MaterialTable[index][1];
	ambient[2] = MaterialTable[index][2];
	ambient[3] = MaterialTable[index][3];
	diffuse[0] = MaterialTable[index][4];
	diffuse[1] = MaterialTable[index][5];
	diffuse[2] = MaterialTable[index][6];
	diffuse[3] = MaterialTable[index][7];
	specular[0] = MaterialTable[index][8];
	specular[1] = MaterialTable[index][9];
	specular[2] = MaterialTable[index][10];
	specular[3] = MaterialTable[index][11];
	shininess = MaterialTable[index][12];
}

void Material::reset() {
	ambient[0] = 0.8;
	ambient[1] = 0.8;
	ambient[2] = 0.8;
	ambient[3] = 0.8;
	diffuse[0] = 0.8;
	diffuse[1] = 0.8;
	diffuse[2] = 0.8;
	diffuse[3] = 0.8;
	specular[0] = 0.5;
	specular[1] = 0.5;
	specular[2] = 0.5;
	specular[3] = 0.5;
	shininess = 0.;
}
