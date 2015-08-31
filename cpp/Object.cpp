#include "stdafx.h" 
#include "Object.h"

const double expand = 2;

TexturePainter mPainter;

Object::Object(int id, Type type) {
	mId = id;
	mType = type;
	mTextureIndex = -1;
	mTextureName = "None";
	mRotateFlag = false;
}

Object::Object(int id, Type type, Color color, Translate translate, Rotate rotate) {
	mId = id;
	mType = type;
	mColor = color;
	mTranslate = translate;
	mRotate = rotate;
	mTextureIndex = -1;
	mTextureName = "None";
	mRotateFlag = false;
}

Object::~Object() {
}

int Object::getId() {
	return mId;
}

Type Object::getType() {
	return mType;
}

Color Object::getCol() {
	return mColor;
}

Translate Object::getTra() {
	return mTranslate;
}

Rotate Object::getRot() {
	return mRotate;
}

Material Object::getMat() {
	return mMaterial;
}

vector<CString> Object::getColor() {
	vector<CString> ret(4, CString());
	ret[0].Format(_T("%d"), mColor.r);
	ret[1].Format(_T("%d"), mColor.g);
	ret[2].Format(_T("%d"), mColor.b);
	ret[3].Format(_T("%d"), mColor.a);
	return ret;
}

vector<CString> Object::getTranslate() {
	vector<CString> ret(3, CString());
	ret[0].Format(_T("%.2f"), mTranslate.x);
	ret[1].Format(_T("%.2f"), mTranslate.y);
	ret[2].Format(_T("%.2f"), mTranslate.z);
	return ret;
}

vector<CString> Object::getRotate() {
	vector<CString> ret(4, CString());
	ret[0].Format(_T("%.1f"), mRotate.angle);
	ret[1].Format(_T("%.2f"), mRotate.x);
	ret[2].Format(_T("%.2f"), mRotate.y);
	ret[3].Format(_T("%.2f"), mRotate.z);
	return ret;
}

CString Object::getTextureName() {
	return mTextureName;
}
vector<CString> Object::getMaterial() {
	vector<CString> ret(13, CString());
	ret[0].Format(_T("%f"), mMaterial.ambient[0]);
	ret[1].Format(_T("%f"), mMaterial.ambient[1]);
	ret[2].Format(_T("%f"), mMaterial.ambient[2]);
	ret[3].Format(_T("%f"), mMaterial.ambient[3]);
	ret[4].Format(_T("%f"), mMaterial.diffuse[0]);
	ret[5].Format(_T("%f"), mMaterial.diffuse[1]);
	ret[6].Format(_T("%f"), mMaterial.diffuse[2]);
	ret[7].Format(_T("%f"), mMaterial.diffuse[3]);
	ret[8].Format(_T("%f"), mMaterial.specular[0]);
	ret[9].Format(_T("%f"), mMaterial.specular[1]);
	ret[10].Format(_T("%f"), mMaterial.specular[2]);
	ret[11].Format(_T("%f"), mMaterial.specular[3]);
	ret[12].Format(_T("%f"), mMaterial.shininess);
	return ret;
}

void Object::setAttribute(Color color, Translate translate, Rotate rotate) {
	mTranslate = translate;
	mRotate = rotate;
}

void Object::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	setAttribute(color, translate, rotate);
}

void Object::setAttribute(Translate translate) {
	mUpperBound[0] += translate.x - mTranslate.x;
	mUpperBound[1] += translate.y - mTranslate.y;
	mUpperBound[2] += translate.z - mTranslate.z;
	mLowerBound[0] += translate.x - mTranslate.x;
	mLowerBound[1] += translate.y - mTranslate.y;
	mLowerBound[2] += translate.z - mTranslate.z;
	mTranslate = translate;
}

void Object::setAttribute(Rotate rotate) {
	mRotate = rotate;
}

void Object::setAttribute(Color color) {
	mColor = color;
}

void Object::setAttribute(Material material) {
	mMaterial = material;
}

void Object::setAttribute(int textureIndex) {
	mTextureIndex = textureIndex;
}

void Object::setAttribute(CString textureName) {
	mTextureName = textureName;
}

void Object::setMaterial(MaterialType type) {
	Material material;
	material.setMaterial(type);
	mMaterial = material;
}

void Object::enableRotate() {
	mRotateFlag = true;
}

void Object::disableRotate() {
	mRotateFlag = false;
}

void Object::drawBegin() {
	glPushMatrix(); 
	mMaterial.show();
	if (mRotateFlag) {
		mRotate.angle += 1;
	}
	glTranslated(mTranslate.x, mTranslate.y, mTranslate.z);
	glRotated(mRotate.angle, mRotate.x, mRotate.y, mRotate.z);
	glColor4f(mColor.r / 255.0, mColor.g / 255.0, mColor.b / 255.0, mColor.a);
	if (mTextureIndex >= 0) glEnable(GL_TEXTURE_2D);
}

void Object::drawEnd() {
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

bool Object::test(double x, double y, double z) {
	if (testX(x) == false && testY(y) == false && testZ(z) == false)
		return false;
	else 
		return true;
}

bool Object::testX(double x) {
	if (x < mUpperBound[0] + expand && x > mLowerBound[0] - expand)
		return false;
	else
		return true;
}

bool Object::testY(double y) {
	if (y < mUpperBound[1] + expand && y > mLowerBound[1] - expand)
		return false;
	else
		return true;
}

bool Object::testZ(double z) {
	if (z < mUpperBound[2] + expand && z > mLowerBound[2] - expand)
		return false;
	else
		return true;
}




///////////////////////////Cube////////////////////////////

Cube::Cube(int id, Type type) : Object(id, type) {
	mUpperBound[0] = mPara.length / 2 + mTranslate.x;
	mLowerBound[0] = -mPara.length / 2 + mTranslate.x;
	mUpperBound[1] = mPara.height / 2 + mTranslate.y;
	mLowerBound[1] = -mPara.height / 2 + mTranslate.y;
	mUpperBound[2] = mPara.width / 2 + mTranslate.z;
	mLowerBound[2] = -mPara.width / 2 + mTranslate.z;
}

Cube::Cube(int id, Type type, Color color, Translate translate, Rotate rotate, CubeParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Cube::~Cube() {
}

void Cube::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Cube::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("length")));
	ret.push_back(CString(_T("width")));
	ret.push_back(CString(_T("height")));
	return ret;
}

vector<CString> Cube::getParaValue() {
	vector<CString> ret(3, CString());
	ret[0].Format(_T("%.2f"), mPara.length);
	ret[1].Format(_T("%.2f"), mPara.width);
	ret[2].Format(_T("%.2f"), mPara.height);
	return ret;
}

map<CString, CString> Cube::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Cube::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Cube::setAttribute(Parameter& para) {
	mPara = *(CubeParameter*)&para;
	mUpperBound[0] = mPara.length / 2 + mTranslate.x;
	mLowerBound[0] = -mPara.length / 2 + mTranslate.x;
	mUpperBound[1] = mPara.height / 2 + mTranslate.y;
	mLowerBound[1] = -mPara.height / 2 + mTranslate.y;
	mUpperBound[2] = mPara.width / 2 + mTranslate.z;
	mLowerBound[2] = -mPara.width / 2 + mTranslate.z;
}

void Cube::draw() {
	drawBegin();
	mPainter.DrawCube(mPara.length, mPara.width, mPara.height, mTextureIndex);
	drawEnd();
}




///////////////////////////Sphere////////////////////////////

Sphere::Sphere(int id, Type type) : Object(id, type) {
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.radius + mTranslate.x;
	mLowerBound[2] = -mPara.radius + mTranslate.x;
}

Sphere::Sphere(int id, Type type, Color color, Translate translate, Rotate rotate, SphereParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Sphere::~Sphere() {
}

void Sphere::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Sphere::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("radius")));
	ret.push_back(CString(_T("iSlices")));
	ret.push_back(CString(_T("iStacks")));
	return ret;
}

vector<CString> Sphere::getParaValue() {
	vector<CString> ret(3, CString());
	ret[0].Format(_T("%.2f"), mPara.radius);
	ret[1].Format(_T("%d"), mPara.iSlices);
	ret[2].Format(_T("%d"), mPara.iStacks);
	return ret;
}

map<CString, CString> Sphere::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Sphere::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Sphere::setAttribute(Parameter& para) {
	mPara = *(SphereParameter*)&para;
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.radius + mTranslate.x;
	mLowerBound[2] = -mPara.radius + mTranslate.x;
}

void Sphere::draw() {
	drawBegin();
	mPainter.DrawSphere(mPara.radius, mPara.iSlices, mPara.iStacks, mTextureIndex);
	drawEnd();
}




///////////////////////////Cylinder////////////////////////////

Cylinder::Cylinder(int id, Type type) : Object(id, type) {
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

Cylinder::Cylinder(int id, Type type, Color color, Translate translate, Rotate rotate, CylinderParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Cylinder::~Cylinder() {
}

void Cylinder::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Cylinder::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("radius")));
	ret.push_back(CString(_T("height")));
	ret.push_back(CString(_T("iSlices")));
	ret.push_back(CString(_T("iStacks")));
	return ret;
}

vector<CString> Cylinder::getParaValue() {
	vector<CString> ret(4, CString());
	ret[0].Format(_T("%.2f"), mPara.radius);
	ret[1].Format(_T("%.2f"), mPara.height);
	ret[2].Format(_T("%d"), mPara.iSlices);
	ret[3].Format(_T("%d"), mPara.iStacks);
	return ret;
}

map<CString, CString> Cylinder::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Cylinder::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Cylinder::setAttribute(Parameter& para) {
	mPara = *(CylinderParameter*)&para;
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

void Cylinder::draw() {
	drawBegin();
	mPainter.DrawCylinder(mPara.radius, mPara.height, mPara.iSlices, mPara.iStacks, mTextureIndex);
	drawEnd();
}




///////////////////////////Prismoid////////////////////////////

Prismoid::Prismoid(int id, Type type) : Object(id, type) {
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

Prismoid::Prismoid(int id, Type type, Color color, Translate translate, Rotate rotate, PrismoidParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Prismoid::~Prismoid() {
}

void Prismoid::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Prismoid::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("surfaceNum")));
	ret.push_back(CString(_T("height")));
	ret.push_back(CString(_T("radius")));
	return ret;
}

vector<CString> Prismoid::getParaValue() {
	vector<CString> ret(3, CString());
	ret[0].Format(_T("%d"), mPara.surfaceNum);
	ret[1].Format(_T("%.2f"), mPara.height);
	ret[2].Format(_T("%.2f"), mPara.radius);
	return ret;
}

map<CString, CString> Prismoid::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Prismoid::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Prismoid::setAttribute(Parameter& para) {
	mPara = *(PrismoidParameter*)&para;
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

void Prismoid::draw() {
	drawBegin();
	mPainter.DrawPrismoid(mPara.surfaceNum, mPara.height, mPara.radius, mTextureIndex);
	drawEnd();
}




///////////////////////////Cone////////////////////////////

Cone::Cone(int id, Type type) : Object(id, type) {
	mUpperBound[0] = mPara.base + mTranslate.x;
	mLowerBound[0] = -mPara.base + mTranslate.x;
	mUpperBound[1] = mPara.base + mTranslate.x;
	mLowerBound[1] = -mPara.base + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

Cone::Cone(int id, Type type, Color color, Translate translate, Rotate rotate, ConeParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Cone::~Cone() {
}

void Cone::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Cone::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("base")));
	ret.push_back(CString(_T("height")));
	ret.push_back(CString(_T("iSlices")));
	ret.push_back(CString(_T("iStacks")));
	return ret;
}

vector<CString> Cone::getParaValue() {
	vector<CString> ret(4, CString());
	ret[0].Format(_T("%.2f"), mPara.base);
	ret[1].Format(_T("%.2f"), mPara.height);
	ret[2].Format(_T("%d"), mPara.iSlices);
	ret[3].Format(_T("%d"), mPara.iStacks);
	return ret;
}

map<CString, CString> Cone::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Cone::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Cone::setAttribute(Parameter& para) {
	mPara = *(ConeParameter*)&para;
	mUpperBound[0] = mPara.base + mTranslate.x;
	mLowerBound[0] = -mPara.base + mTranslate.x;
	mUpperBound[1] = mPara.base + mTranslate.x;
	mLowerBound[1] = -mPara.base + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

void Cone::draw() {
	drawBegin();
	mPainter.DrawCone(mPara.base, mPara.height, mPara.iSlices, mPara.iStacks, mTextureIndex);
	drawEnd();
}




///////////////////////////Trustum////////////////////////////

Trustum::Trustum(int id, Type type) : Object(id, type) {
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

Trustum::Trustum(int id, Type type, Color color, Translate translate, Rotate rotate, TrustumParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Trustum::~Trustum() {
}

void Trustum::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Trustum::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("surfaceNum")));
	ret.push_back(CString(_T("height")));
	ret.push_back(CString(_T("radius")));
	ret.push_back(CString(_T("scale")));
	return ret;
}

vector<CString> Trustum::getParaValue() {
	vector<CString> ret(4, CString());
	ret[0].Format(_T("%d"), mPara.surfaceNum);
	ret[1].Format(_T("%.2f"), mPara.height);
	ret[2].Format(_T("%.2f"), mPara.radius);
	ret[3].Format(_T("%.2f"), mPara.scale);
	return ret;
}

map<CString, CString> Trustum::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Trustum::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Trustum::setAttribute(Parameter& para) {
	mPara = *(TrustumParameter*)&para;
	mUpperBound[0] = mPara.radius + mTranslate.x;
	mLowerBound[0] = -mPara.radius + mTranslate.x;
	mUpperBound[1] = mPara.radius + mTranslate.x;
	mLowerBound[1] = -mPara.radius + mTranslate.x;
	mUpperBound[2] = mPara.height + mTranslate.x;
	mLowerBound[2] = 0 + mTranslate.x;
}

void Trustum::draw() {
	drawBegin();
	mPainter.DrawTrustum(mPara.surfaceNum, mPara.height, mPara.radius, mPara.scale, mTextureIndex);
	drawEnd();
}




///////////////////////////Import////////////////////////////

Import::Import(int id, Type type) : Object(id, type) {
}

Import::Import(int id, Type type, Color color, Translate translate, Rotate rotate, ImportParameter para) : Object(id, type, color, translate, rotate) {
	mPara = para;
}

Import::~Import() {
}

void Import::getParameter(Parameter* para) {
	*para = mPara;
}

vector<CString> Import::getParaName() {
	vector<CString> ret;
	ret.push_back(CString(_T("fileName")));
	return ret;
}

vector<CString> Import::getParaValue() {
	vector<CString> ret(1, CString());
	ret[0] = mPara.fileName;
	return ret;
}

map<CString, CString> Import::getPara() {
	map<CString, CString> ret;
	vector<CString> paraName = getParaName();
	vector<CString> paraValue = getParaValue();
	for (int i = 0; i < paraName.size(); i++) {
		ret[paraName[i]] = paraValue[i];
	}
	return ret;
}

void Import::setAttribute(Parameter& para, Color color, Translate translate, Rotate rotate) {
	Object::setAttribute(color, translate, rotate);
	setAttribute(para);
}

void Import::setAttribute(Parameter& para) {
	mPara = *(ImportParameter*)&para;
	string strTemp = toString(mPara.fileName);
	mImporter.ProcessFileInfo(strTemp);
}

void Import::draw() {
	drawBegin();
	mImporter.DrawObject();
	drawEnd();
}

void Import::saveObject(string fileName) {
	mImporter.saveObject(fileName);
}
