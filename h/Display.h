#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>

#include "Object.h"
using namespace std;

class Display {

public:
	Display(SpotLight& sLight, DirectLight& dLight);
	~Display();

	int add(Type type);
	int addImportObject(CString fileName);
	int addMazeCube(Translate translate);
	void del(int id);
	void update(int id, Parameter& para);
	void update(int id, vector<CString> paraData);	//直接用CString设置属性
	void update(int id, Translate translate);
	void update(int id, Rotate rotate);
	void update(int id, Color color);
	void update(int id, Material material);		//设置材质，材质属性有颜色和镜面反射率，具体见Material.h
	void update(int id, int defaultTextureIndex);		//设置纹理
	void update(int id, CString textureFileName);
	void initTexture();//这个函数需要在initOpengl里面先执行一次，载入默认纹理
	void setMaterial(int id, MaterialType type);
	void setMaterial(int id, int typeIndex);
	void enableRotate(int id);
	void disableRotate(int id);
	void enableRotate();
	void disableRotate();

	void show();

	Type getType(int id);
	Color getCol(int id);
	Translate getTra(int id);
	Rotate getRot(int id);
	Material getMat(int id);
	CString getTextureName(int id);
	void getParameter(int id, Parameter* para);

	vector<CString> getColor(int id);
	vector<CString> getTranslate(int id);
	vector<CString> getRotate(int id);
	vector<CString> getParaName(int id);
	vector<CString> getParaValue(int id);
	map<CString, CString> getPara(int id);

	void exportObj(CString fileName);
	map<int, Type> importObj(CString fileName);
	void exportObj(string fileName);
	map<int, Type> importObj(string fileName);

	bool test(double x, double y, double z);

	void enableMaze();
	void disableMaze();
	bool isInMaze();

	static const double floorThick;
	static const double mazeCubeSize;
	static const int mazeLength;

private:
	void enableMaterial();
	void disableMaterial();
	GLint getTexture(LPCWSTR fileName);			//通过文件名获取纹理编号
	GLint getTexture(int defaultTextureIndex);	//通过默认纹理的下标获取纹理编号默认的有三个

	vector<Object*> objects;
	int idAllocator;

	map<LPCWSTR, int> textureTable;
	vector<LPCWSTR> defaultTexture;

	SpotLight& spotLight;
	DirectLight& directLight;
	
	bool mazeFlag;
	vector<Object*> oldObjects;
	int oldIdAllocator;

	void turnToMaze();
};

string toString(CString str);


#endif
