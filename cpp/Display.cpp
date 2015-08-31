#include "stdafx.h" 
#include "Display.h"

using namespace std;
const double Display::floorThick = 4;
const double Display::mazeCubeSize = 10;
const int Display::mazeLength = 11;
bool maze[Display::mazeLength][Display::mazeLength] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

extern TexturePainter mPainter;

Display::Display(SpotLight& sLight, DirectLight& dLight) : spotLight(sLight), directLight(dLight) {
	idAllocator = 0;
	mazeFlag = false;
}

Display::~Display() {
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}

int Display::add(Type type) {
	Object* newObject;
	switch (type) {
	case CUBE:
		newObject = new Cube(idAllocator, type);
		break;
	case SPHERE:
		newObject = new Sphere(idAllocator, type);
		break;
	case CYLINDER:
		newObject = new Cylinder(idAllocator, type);
		break;
	case PRISMOID:
		newObject = new Prismoid(idAllocator, type);
		break;
	case CONE:
		newObject = new Cone(idAllocator, type);
		break;
	case TRUSTUM:
		newObject = new Trustum(idAllocator, type);
		break;
	default:
		break;
	}
	objects.push_back(newObject);
	return idAllocator++;
}

int Display::addImportObject(CString fileName) {
	Object* newObject = new Import(idAllocator, IMPORT);
	Parameter *para = new ImportParameter(fileName);
	newObject->setAttribute(*para);
	delete para;
	objects.push_back(newObject);
	return idAllocator++;
}

int Display::addMazeCube(Translate translate) {
	Object* newObject;
	newObject = new Cube(idAllocator, CUBE);
	CubeParameter para(mazeCubeSize, mazeCubeSize, mazeCubeSize);
	newObject->setAttribute(para);
	newObject->setAttribute(translate);
	objects.push_back(newObject);
	return idAllocator++;
}

void Display::del(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			break;
		}
	}
}

void Display::update(int id, Parameter& para) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(para);
			break;
		}
	}
}

void Display::update(int id, vector<CString> paraData) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			Type type = objects[i]->getType();
			switch (type) {
			case CUBE:
				objects[i]->setAttribute(CubeParameter(_ttof(paraData[0]), _ttof(paraData[1]), _ttof(paraData[2])));
				break;
			case SPHERE:
				objects[i]->setAttribute(SphereParameter(_ttof(paraData[0]), _ttoi(paraData[1]), _ttoi(paraData[2])));
				break;
			case CYLINDER:
				objects[i]->setAttribute(CylinderParameter(_ttof(paraData[0]), _ttof(paraData[1]), _ttoi(paraData[2]), _ttoi(paraData[3])));
				break;
			case PRISMOID:
				objects[i]->setAttribute(PrismoidParameter(_ttoi(paraData[0]), _ttof(paraData[1]), _ttof(paraData[2])));
				break;
			case CONE:
				objects[i]->setAttribute(ConeParameter(_ttof(paraData[0]), _ttof(paraData[1]), _ttoi(paraData[2]), _ttoi(paraData[3])));
				break;
			case TRUSTUM:
				objects[i]->setAttribute(TrustumParameter(_ttoi(paraData[0]), _ttof(paraData[1]), _ttof(paraData[2]), _ttof(paraData[3])));
				break;
			default:
				break;
			}
		}
	}
}

void Display::update(int id, Translate translate) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(translate);
			break;
		}
	}
}

void Display::update(int id, Rotate rotate) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(rotate);
			break;
		}
	}
}

void Display::update(int id, Color color) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(color);
			break;
		}
	}
}

void Display::update(int id, Material material) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(material);
			break;
		}
	}
}

void Display::update(int id, int defaultTextureIndex) {
	GLint textureIndex = defaultTextureIndex;
	if (defaultTextureIndex >= 0) {
		textureIndex = getTexture(defaultTextureIndex);
	}
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(textureIndex);
			if (defaultTextureIndex >= 0) {
				objects[i]->setAttribute(defaultTexture[defaultTextureIndex]);
			}
			else {
				objects[i]->setAttribute(_T("None"));
			}
			break;
		}
	}
}

void Display::update(int id, CString textureFileName) {
	GLint textureIndex = getTexture((LPCWSTR)textureFileName);
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setAttribute(textureIndex);
			if (textureIndex >= 0) {
				objects[i]->setAttribute(textureFileName);
			}
			else {
				objects[i]->setAttribute(_T("None"));
			}
			break;
		}
	}
}

void Display::enableMaterial() {
	Material::enable();
}

void Display::disableMaterial() {
	Material::disable();
}

void Display::setMaterial(int id, MaterialType type) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->setMaterial(type);
			break;
		}
	}
}

void Display::setMaterial(int id, int typeIndex) {
	setMaterial(id, MaterialType(typeIndex));
}

void Display::enableRotate(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->enableRotate();
			break;
		}
	}
}

void Display::disableRotate(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->disableRotate();
			break;
		}
	}
}

void Display::enableRotate() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->enableRotate();
	}
}

void Display::disableRotate() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->disableRotate();
	}
}

void Display::show() {
	if (Light::flag[0] || Light::flag[1]) {
		glEnable(GL_LIGHTING);
		enableMaterial();
	}
	if (Light::flag[0]) {
		spotLight.show();
	}
	if (Light::flag[1]) {
		directLight.show();
	}
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
	glDisable(GL_LIGHTING);
	disableMaterial();
}

Type Display::getType(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getType();
		}
	}
	return UNKNOWN;
}

Color Display::getCol(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getCol();
		}
	}
	return Color();
}

Translate Display::getTra(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getTra();
		}
	}
	return Translate();
}

Rotate Display::getRot(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getRot();
		}
	}
	return Rotate();
}

Material Display::getMat(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getMat();
		}
	}
	return Material();
}

CString Display::getTextureName(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getTextureName();
		}
	}
	return CString();
}

void Display::getParameter(int id, Parameter* para) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			objects[i]->getParameter(para);
			return;
		}
	}
	*para = Parameter();
	return;
}

vector<CString> Display::getColor(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getColor();
		}
	}
	return vector<CString>();
}

vector<CString> Display::getTranslate(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getTranslate();
		}
	}
	return vector<CString>();
}

vector<CString> Display::getRotate(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getRotate();
		}
	}
	return vector<CString>();
}

vector<CString> Display::getParaName(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getParaName();
		}
	}
	return vector<CString>();
}

vector<CString> Display::getParaValue(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getParaValue();
		}
	}
	return vector<CString>();
}

map<CString, CString> Display::getPara(int id) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i]->getPara();
		}
	}
	return map<CString, CString>();
}

GLint Display::getTexture(LPCWSTR fileName) {
	if (textureTable.count(fileName) == 1) {
		return textureTable[fileName];
	}
	else {
		return textureTable[fileName] = mPainter.LoadTexture(fileName);
	}
}

GLint Display::getTexture(int defaultTextureIndex) {
	return getTexture(defaultTexture[defaultTextureIndex]);
}

void Display::initTexture() {
	textureTable[_T("texture/texture0.bmp")] = mPainter.LoadTexture(_T("texture/texture0.bmp"));
	defaultTexture.push_back(_T("texture/texture0.bmp"));
	textureTable[_T("texture/texture1.bmp")] = mPainter.LoadTexture(_T("texture/texture1.bmp"));
	defaultTexture.push_back(_T("texture/texture1.bmp"));
	textureTable[_T("texture/texture2.bmp")] = mPainter.LoadTexture(_T("texture/texture2.bmp"));
	defaultTexture.push_back(_T("texture/texture2.bmp"));
	glDisable(GL_TEXTURE_2D);
}

void Display::exportObj(CString fileName) {
	exportObj(toString(fileName));
}

void Display::exportObj(string fileName) {
	ofstream ofs;
	ofs.open(fileName.c_str());
	for (int i = 0; i < objects.size(); i++) {
		ofs << objects[i]->getType() << endl;
		if (objects[i]->getType() != IMPORT) {
			vector<CString> paraValue = objects[i]->getParaValue();
			for (int j = 0; j < paraValue.size(); j++) {
				ofs << CStringA(paraValue[j]) << endl;
			}
		}
		else {
			char temp[10];
			sprintf(temp, "%d", i);
			string strTemp = temp;
			string objFileName = fileName;
			int j;
			for (j = objFileName.length() - 1; j >= 0 && objFileName.at(j) != '.'; j--)
				;
			for (int k = strTemp.length() - 1; k >= 0; k--) {
				objFileName.insert(objFileName.begin() + j, strTemp.at(k));
			}
			objFileName.insert(objFileName.begin() + j, 'j');
			objFileName.insert(objFileName.begin() + j, 'b');
			objFileName.insert(objFileName.begin() + j, 'O');
			objFileName.insert(objFileName.begin() + j, '_');
			((Import*)objects[i])->saveObject(objFileName);
			ofs << objFileName << endl;
		}
		vector<CString> tran = objects[i]->getTranslate();
		for (int j = 0; j < tran.size(); j++) {
			ofs << CStringA(tran[j]) << endl;
		}
		vector<CString> rota = objects[i]->getRotate();
		for (int j = 0; j < rota.size(); j++) {
			ofs << CStringA(rota[j]) << endl;
		}
		vector<CString> colo = objects[i]->getColor();
		for (int j = 0; j < colo.size(); j++) {
			ofs << CStringA(colo[j]) << endl;
		}
		CString texName = objects[i]->getTextureName();
		ofs << CStringA(texName) << endl;
		vector<CString> mate = objects[i]->getMaterial();
		for (int j = 0; j < mate.size(); j++) {
			ofs << CStringA(mate[j]) << endl;
		}
	}
	ofs.close();
}

map<int, Type> Display::importObj(CString fileName) {
	return importObj(toString(fileName));
}

map<int, Type> Display::importObj(string fileName) {
	map<int, Type> ret;
	int number[7] = { 3, 3, 4, 3, 4, 4, 1 };
	FILE* file = fopen(fileName.c_str(), "r");
	Type type;
	while (fscanf(file, "%d\n", &type) != EOF) {
		//getPara from file
		int id;
		if (type != IMPORT) {
			id = add(type);
			ret[id] = type;
			vector<double> paraValue;
			for (int i = 0; i < number[type]; i++) {
				double temp;
				fscanf(file, "%lf\n", &temp);
				paraValue.push_back(temp);
			}
			Parameter* para;
			switch (type) {
			case CUBE:
				para = new CubeParameter(paraValue[0], paraValue[1], paraValue[2]);
				break;
			case SPHERE:
				para = new SphereParameter(paraValue[0], paraValue[1], paraValue[2]);
				break;
			case CYLINDER:
				para = new CylinderParameter(paraValue[0], paraValue[1], paraValue[2], paraValue[3]);
				break;
			case PRISMOID:
				para = new PrismoidParameter(paraValue[0], paraValue[1], paraValue[2]);
				break;
			case CONE:
				para = new ConeParameter(paraValue[0], paraValue[1], paraValue[2], paraValue[3]);
				break;
			case TRUSTUM:
				para = new TrustumParameter(paraValue[0], paraValue[1], paraValue[2], paraValue[3]);
				break;
			}
			update(id, *para);
			delete para;
		}
		else {
			CString objectImportedFileName;
			char temp[100];
			fscanf(file, "%s\n", temp);
			objectImportedFileName = temp;
			id = addImportObject(objectImportedFileName);
			ret[id] = type;
		}

		//getTranslate from file
		Translate tra;
		fscanf(file, "%lf\n", &tra.x);
		fscanf(file, "%lf\n", &tra.y);
		fscanf(file, "%lf\n", &tra.z);
		update(id, tra);

		Rotate rot;
		fscanf(file, "%lf\n", &rot.angle);
		fscanf(file, "%lf\n", &rot.x);
		fscanf(file, "%lf\n", &rot.y);
		fscanf(file, "%lf\n", &rot.z);
		update(id, rot);

		Color col;
		fscanf(file, "%d\n", &col.r);
		fscanf(file, "%d\n", &col.g);
		fscanf(file, "%d\n", &col.b);
		fscanf(file, "%d\n", &col.a);
		update(id, col);

		CString texName;
		char tempTexName[100];
		fscanf(file, "%s\n", tempTexName);
		texName = tempTexName;
		if (texName != "None") 
			update(id, texName);

		Material mat;
		for (int i = 0; i < 4; i++) {
			fscanf(file, "%f\n", mat.ambient + i);
		}
		for (int i = 0; i < 4; i++) {
			fscanf(file, "%f\n", mat.diffuse + i);
		}
		for (int i = 0; i < 4; i++) {
			fscanf(file, "%f\n", mat.specular + i);
		}
		fscanf(file, "%f\n", &mat.shininess);
		update(id, mat);
	}
	return ret;
}

bool Display::test(double x, double y, double z) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->test(x, y, z) == false) {
			return false;
		}
	}
	return true;
}

void Display::enableMaze() {
	oldObjects = objects;
	oldIdAllocator = idAllocator;
	objects.clear();
	idAllocator = 0;
	turnToMaze();
	mazeFlag = true;
}

void Display::disableMaze() {
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	objects = oldObjects;
	idAllocator = oldIdAllocator;
	mazeFlag = false;
}

bool Display::isInMaze() {
	return mazeFlag;
}

void Display::turnToMaze() {
	//µØ°å
	int id = add(CUBE);
	CubeParameter para(mazeLength * mazeCubeSize, mazeLength * mazeCubeSize, floorThick);
	update(id, para);
	//Ç½
	for (int i = 0; i < mazeLength; i++) {
		for (int j = 0; j < mazeLength; j++) {
			if (maze[i][j]) {
				Translate translate(-(mazeLength / 2) * mazeCubeSize + j * mazeCubeSize, mazeCubeSize / 2 + floorThick / 2, -(mazeLength / 2) * mazeCubeSize + i * mazeCubeSize);
				addMazeCube(translate);
			}
		}
	}
}

string toString(CString str) {
	return string((LPCSTR)CStringA(str));
}


