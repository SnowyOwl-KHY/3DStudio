#ifndef _OBJECT_H
#define _OBJECT_H
#include "stdafx.h" 
#include <Windows.h>
#include "GL/glut.h"
#include <vector>
#include <map>
#pragma once

#include "Attribute.h"
#include "ModelPainter.h"
#include "Material.h"

using namespace std;

class Object {

public:
	Object(int id, Type type);
	Object(int id, Type type, Color color, Translate translate, Rotate rotate);
	virtual ~Object();

	int getId();
	Type getType();
	Color getCol();
	Translate getTra();
	Rotate getRot();
	Material getMat();
	virtual void getParameter(Parameter* para) = 0;
	vector<CString> getColor();
	vector<CString> getTranslate();
	vector<CString> getRotate();
	CString getTextureName();
	vector<CString> getMaterial();
	virtual vector<CString> getParaName() = 0;
	virtual vector<CString> getParaValue() = 0;
	virtual map<CString, CString> getPara() = 0;
	
	void setAttribute(Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& para) = 0;
	void setAttribute(Translate translate);
	void setAttribute(Rotate rotate);
	void setAttribute(Color color);
	void setAttribute(Material material);
	void setAttribute(int textureIndex);
	void setAttribute(CString textureName);
	void setMaterial(MaterialType type);

	void enableRotate();
	void disableRotate();

	virtual void draw() = 0;
	void drawBegin();
	void drawEnd();

	bool test(double x, double y, double z);

protected:
	bool testX(double x);
	bool testY(double y);
	bool testZ(double z);

	int mId;
	Type mType;
	Color mColor;
	Translate mTranslate;
	Rotate mRotate;
	Material mMaterial;
	int mTextureIndex;
	CString mTextureName;
	double mUpperBound[3];
	double mLowerBound[3];
	bool mRotateFlag;
};



///////////////////////////Cube/////////////////////////////
class Cube : public Object {
public:
	Cube(int id, Type type);
	Cube(int id, Type type, Color color, Translate translate, Rotate rotate, CubeParameter para);
	virtual ~Cube();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();

protected:
	CubeParameter mPara;
};



///////////////////////////Sphere/////////////////////////////
class Sphere : public Object {
public:
	Sphere(int id, Type type);
	Sphere(int id, Type type, Color color, Translate translate, Rotate rotate, SphereParameter para);
	virtual ~Sphere();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();

protected:
	SphereParameter mPara;
};



///////////////////////////Cylinder/////////////////////////////
class Cylinder : public Object {
public:
	Cylinder(int id, Type type);
	Cylinder(int id, Type type, Color color, Translate translate, Rotate rotate, CylinderParameter para);
	virtual ~Cylinder();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();

protected:
	CylinderParameter mPara;
};



///////////////////////////Prismoid/////////////////////////////
class Prismoid : public Object {
public:
	Prismoid(int id, Type type);
	Prismoid(int id, Type type, Color color, Translate translate, Rotate rotate, PrismoidParameter para);
	virtual ~Prismoid();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();

protected:
	PrismoidParameter mPara;
};



///////////////////////////Cone/////////////////////////////
class Cone : public Object {
public:
	Cone(int id, Type type);
	Cone(int id, Type type, Color color, Translate translate, Rotate rotate, ConeParameter para);
	virtual ~Cone();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();

protected:
	ConeParameter mPara;
};



///////////////////////////Trustum/////////////////////////////
class Trustum : public Object {
public:
	Trustum(int id, Type type);
	Trustum(int id, Type type, Color color, Translate translate, Rotate rotate, TrustumParameter para);
	virtual ~Trustum();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();

protected:
	TrustumParameter mPara;
};



///////////////////////////Import/////////////////////////////
class Import : public Object {
public:
	Import(int id, Type type);
	Import(int id, Type type, Color color, Translate translate, Rotate rotate, ImportParameter para);
	virtual ~Import();
	virtual void getParameter(Parameter* para);
	virtual vector<CString> getParaName();
	virtual vector<CString> getParaValue();
	virtual map<CString, CString> getPara();
	virtual void setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate);
	virtual void setAttribute(Parameter& pare);
	virtual void draw();
	void saveObject(string FileName);

protected:
	ImportParameter mPara;
private:
	objImporter mImporter;
};


#endif
