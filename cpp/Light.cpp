
#include "StdAfx.h"
#include "Light.h"
using namespace std;

////////////////////////////Light////////////////////////////

GLenum Light::lightId[2];
bool Light::flag[2];

Light::Light() {
	position[0] = 0.0;
	position[1] = 800.0;
	position[2] = 0.0;
	position[3] = 1.0;

	Model_Ambient[0] = 0.2;
	Model_Ambient[1] = 0.2;
	Model_Ambient[2] = 0.2;
	Model_Ambient[3] = 1.0;

	lightId[0] = GL_LIGHT0;
	lightId[1] = GL_LIGHT1;
}

Light::~Light() {	
	glDisable(GL_LIGHTING);
}

void Light::enable() {
	flag[id] = true;
	glEnable(lightId[id]);
}

void Light::disable() {
	glDisable(lightId[id]);
	flag[id] = false;
}




////////////////////////////SpotLight////////////////////////////

SpotLight::SpotLight() {
	ambient[0] = 0.2;
	ambient[1] = 0.2;
	ambient[2] = 0.2;
	ambient[3] = 0.2;

	diffuse[0] = 0.8;
	diffuse[1] = 0.8;
	diffuse[2] = 0.8;
	diffuse[3] = 0.8;

	specular[0] = 0.5;
	specular[1] = 0.5;
	specular[2] = 0.5;
	specular[3] = 0.5;

	id = 0;
}

SpotLight::~SpotLight() {
}

void SpotLight::show() {

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Model_Ambient); //设置全局环境光
	glLightfv(lightId[id], GL_POSITION, position);

	glLightfv(lightId[id], GL_AMBIENT, ambient);
	glLightfv(lightId[id], GL_DIFFUSE, diffuse);
	glLightfv(lightId[id], GL_SPECULAR, specular);
}




////////////////////////////DirectLight////////////////////////////

DirectLight::DirectLight() {
	cutoff = 1;
	direction[0] = 0;
	direction[1] = -1;
	direction[2] = 0;
	direction[3] = 1;
	exponent = 2;

	id = 1;
}

DirectLight::~DirectLight() {
}

void DirectLight::show() {
	SpotLight::show();

	glLightf(lightId[id], GL_SPOT_CUTOFF, cutoff);
	glLightfv(lightId[id], GL_SPOT_DIRECTION, direction);
	glLightf(lightId[id], GL_SPOT_EXPONENT, exponent);
}

