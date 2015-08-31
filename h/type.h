#ifndef TYPE_H_
#define TYPE_H_

#include <iostream>
#include <stdio.h>
#include "gl/glut.h"

#define MAX_NAME 30
#define MAX_VERTEX 256
#define MAX_FACE 100
#define MAX_LINE 100
#define MAX_VERTICES 256

using namespace std;

typedef struct polygon
{
	GLint xmin,xmax,ymin,ymax;/*包围盒*/
	GLfloat xc,yc;/*多边形的中心*/
	GLint nvertices; /*顶点的数目*/
	GLfloat x[MAX_VERTICES];//顶点
	GLfloat y[MAX_VERTICES];
	GLfloat z[MAX_VERTICES];
}polygon;

typedef struct vertex3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}vVertex3,nVertex3;

typedef struct tVertex2   	
{
	GLfloat x;								//用于记录每个顶点X坐标
	GLfloat y;									//Y坐标
}tVertex2; 

typedef struct face
{
	unsigned int v[4];			//点信息索引
	unsigned int nv[4];		//法向量信息索引
	unsigned int tv[4];		//材质信息索引
	unsigned int vertexNum;				//3个点还是4个点
	string materialName;
	bool bMaterials;
}face;

typedef struct mMaterial{
	string newmtl;		//材质名称
	vVertex3 Ka;			//环境反射
	vVertex3 Kd;			//漫反射
	vVertex3 Ks;			//镜面反射
	GLfloat Ns;			//Shinness
	GLfloat illum;		//光照模型描述
}mMaterial;

//整个3D物体的对象数据
typedef struct mImport
{
	string materialPath;
	std::vector<vVertex3> vVertexes;
	std::vector<nVertex3> nVertexes;
	std::vector<tVertex2> tVertexes;
	std::vector<face> faces;
	std::vector<mMaterial> materials;
} mImport;

#endif