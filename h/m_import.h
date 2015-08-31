#ifndef M_IMPORT_H
#define M_IMPORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "gl/glut.h"
#include <stdio.h>
#include <vector>
#include "type.h"

//以下是类定义：
class objImporter
{
	private:
		mImport object;
	public:
		objImporter();
		int ProcessFileInfo(string);
		void saveObject(string FileName);
		void DrawObject();
		vector<string> split(string str,string pattern,int* count);		//字符串拆分函数
};
#endif
