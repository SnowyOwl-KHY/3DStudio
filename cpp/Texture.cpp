#include "StdAfx.h"
#include "texture.h"

#define pi 3.141592653589
#define cube_normal_parameter 0.57735026918962

TexturePainter::TexturePainter()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	
	textureNum = -1;
	g_text = gluNewQuadric();

}

GLuint TexturePainter::LoadTexture(LPCWSTR filename)
{
	textureNum++;
	if (LoadT8(filename, texture[textureNum]) == false) {
		textureNum--;
		return -1;
	}
	return textureNum;
}

bool TexturePainter::LoadT8(LPCWSTR filename, GLuint &texture)//调8位贴图
{
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);         // 装入位图
	if (pImage == NULL)      return false;       // 确保位图数据已经装入
	glGenTextures(1, &texture);                 // 生成纹理
	glBindTexture(GL_TEXTURE_2D, texture);   // 捆绑纹理
	//	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
	//		pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(pImage->data);  //释放位图占据的内存资源
	free(pImage);
	return true;// 返回true
}

void TexturePainter::DrawCube(GLfloat length, GLfloat width, GLfloat height, int index)
{
	GLfloat x = length / 2.0;
	GLfloat y = height / 2.0;
	GLfloat z = width / 2.0;

	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	//TO-DO glEnable(GL_TEXTURE_2D)……
	glBegin(GL_QUADS);
	//正面

	glNormal3f(-cube_normal_parameter, -cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, z);
	glNormal3f(-cube_normal_parameter, -cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(0.0, 1.0);	glVertex3f(-x, y, z);
	glNormal3f(cube_normal_parameter, cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 1.0);	glVertex3f(x, y, z);
	glNormal3f(cube_normal_parameter, -cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 0.0);	glVertex3f(x, -y, z);
	
	//左面
	glNormal3f(-cube_normal_parameter, cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 1.0); glVertex3f(-x, y, z);
	glNormal3f(-cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 1.0); glVertex3f(-x, y, -z);
	glNormal3f(-cube_normal_parameter, -cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, -z);
	glNormal3f(-cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(1.0, 0.0);	glVertex3f(-x, -y, z);

	//背面
	glNormal3f(-cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 1.0); glVertex3f(-x, y, -z);
	glNormal3f(cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(1.0, 1.0); glVertex3f(x, y, -z);
	glNormal3f(cube_normal_parameter, -cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(1.0, 0.0);	glVertex3f(x, -y, -z);
	glNormal3f(-cube_normal_parameter, -cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, -z);

	//右面
	glNormal3f(cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 1.0); glVertex3f(x, y, -z);
	glNormal3f(cube_normal_parameter, cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 1.0); glVertex3f(x, y, z);
	glNormal3f(cube_normal_parameter, -cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 0.0);	glVertex3f(x, -y, z);
	glNormal3f(cube_normal_parameter, -cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 0.0);	glVertex3f(x, -y, -z);

	//底面
	glNormal3f(-cube_normal_parameter, -cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(0.0, 1.0); glVertex3f(-x, -y, z);
	glNormal3f(cube_normal_parameter, -cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 1.0); glVertex3f(x, -y, z);
	glNormal3f(cube_normal_parameter, -cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(1.0, 0.0); glVertex3f(x, -y, -z);
	glNormal3f(-cube_normal_parameter, -cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);

	//顶面
	glNormal3f(-cube_normal_parameter, cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(0.0, 1.0); glVertex3f(-x, y, z);
	glNormal3f(cube_normal_parameter, cube_normal_parameter, cube_normal_parameter);
	glTexCoord2f(1.0, 1.0); glVertex3f(x, y, z);
	glNormal3f(cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(1.0, 0.0); glVertex3f(x, y, -z);
	glNormal3f(-cube_normal_parameter, cube_normal_parameter, -cube_normal_parameter);
	glTexCoord2f(0.0, 0.0); glVertex3f(-x, y, -z);
	glEnd();
	glPopMatrix();

}

void TexturePainter::DrawCone(GLfloat base, GLfloat height, GLint longitude, GLint latitude, int index)
{
	int i, j;
	GLfloat dh = height / ((GLfloat)latitude);
	GLfloat dtheta = 2.0 * pi / ((GLfloat)longitude);
	GLfloat du = 1.0 / ((GLfloat)longitude);
	GLfloat dv = 1.0 / ((GLfloat)latitude);
	GLfloat cotalpha = base / height;
	GLfloat u = 0.0f;
	GLfloat v = 1.0f;
	GLfloat x, y, z, ax, ay, az;
	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	for (i = 0; i<latitude; i++)
	{
		GLfloat h = dh * i;
		GLfloat aboveh = h + dh;
		GLfloat rh = height - h;		//顶底距
		GLfloat aboverh = height - aboveh;
		GLfloat r = rh *cotalpha;
		GLfloat abover = aboverh * cotalpha;
		glBegin(GL_TRIANGLE_STRIP);
		GLfloat u = 0.0f;
		for (j = 0; j <= longitude; j++)
		{
			GLfloat theta = dtheta *j;
			GLfloat sintheta = (GLfloat)(sin(theta));
			GLfloat costheta = (GLfloat)(cos(theta));

			x = costheta * r;
			y = sintheta * r;
			z = h;
			ax = costheta *abover;
			ay = sintheta * abover;
			az = aboveh;
			glTexCoord2f(u, v); glVertex3f(x, y, z);
			glTexCoord2f(u, v - dv); glVertex3f(ax, ay, az);
			u += du;
		}
		glEnd();
		v -= dv;
	}
	glPopMatrix();
	//画底面：
	DrawCircle(base, 0, latitude, longitude, false, index);

}


void TexturePainter::DrawCircle(GLfloat r, GLfloat zdata, GLint rsplit, GLint thetasplit, bool upNormal, int index)
{
	int i, j;
	GLfloat dtheta = 2.0* pi / thetasplit;
	GLfloat dr = r / rsplit;
	GLfloat u = 0.0f;
	GLfloat v = 1.0f;
	GLfloat du = 1.0 / ((GLfloat)thetasplit);
	GLfloat dv = 1.0 / ((GLfloat)rsplit);

	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	upNormal = false;
	for (i = 0; i<rsplit; i++)
	{
		GLfloat radius = (GLfloat)(i*dr);
		GLfloat nextRadius = radius + dr;
		GLfloat u = 0.0f;
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= thetasplit; j++)
		{
			GLfloat theta = (GLfloat)(j*dtheta);
			GLfloat costheta = (GLfloat)(cos(theta));
			GLfloat sintheta = (GLfloat)(sin(theta));

			GLfloat x = (GLfloat)(radius *costheta);
			GLfloat y = (GLfloat)(radius *sintheta);
			GLfloat z = zdata;
			if (!upNormal)
				glNormal3f(0.0, 0.0, -1);
			else
				glNormal3f(0.0, 0.0, 1);

			glTexCoord2f(u, v);
			glVertex3f(x, y, z);
			GLfloat ax = (GLfloat)(nextRadius *costheta);
			GLfloat ay = (GLfloat)(nextRadius *sintheta);
			GLfloat az = zdata;

			if (!upNormal)
				glNormal3f(0.0, 0.0, -1);
			else
				glNormal3f(0.0, 0.0, 1);

			glTexCoord2f(u, v - dv);
			glVertex3f(ax, ay, az);
			u += du;
		}

		glEnd();
		v -= dv;
	}
	glPopMatrix();

}

void TexturePainter::DrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks, int index)
{
	GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
	GLfloat ds = 1.0f / (GLfloat)iSlices;
	GLfloat dt = 1.0f / (GLfloat)iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
	GLint i, j;     // Looping variables

	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	for (i = 0; i < iStacks; i++)
	{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for (j = 0; j <= iSlices; j++)
		{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
			glTexCoord2f(s, t);
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
			s += ds;
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);
		}
		glEnd();
		t -= dt;
	}
	glPopMatrix();
}




void TexturePainter::DrawTrustum(GLint surfaceNum, GLfloat height, GLfloat r, GLfloat scale, int index)
{
	int j;
	//计算正多边形的分割角度：
	GLfloat dtheta = 2.0f * pi / ((GLfloat)surfaceNum);
	GLfloat u = 0.0f;
	GLfloat v = 1.0f;
	GLfloat dv = 1.0 / height;
	GLfloat du = 1.0 / ((GLfloat)surfaceNum);

	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	glBegin(GL_TRIANGLE_STRIP);
	for (j = 0; j <= surfaceNum; j++)
	{
		GLfloat theta = (GLfloat)((j - 1 / 2) * dtheta);
		GLfloat costheta = (GLfloat)(cos(theta));
		GLfloat sintheta = (GLfloat)(sin(theta));

		GLfloat x = r*costheta;
		GLfloat y = r*sintheta;
		GLfloat z = 0;
		glTexCoord2f(u, 0.0f);
		glVertex3f(x, y, z);


		GLfloat ax = (GLfloat)(x*scale);
		GLfloat ay = (GLfloat)(y*scale);
		GLfloat az = height;
		glTexCoord2f(u, 1.0f);
		glVertex3f(ax, ay, az);
		u += du;
	}
	glEnd();
	glPopMatrix();
	//画顶面底面：
	DrawPolygon(surfaceNum, 0.0f, r, index);
	DrawPolygon(surfaceNum, height, r*scale, index);
	


}

void TexturePainter::DrawPrismoid(GLint surfaceNum, GLfloat height, GLfloat r, int index)
{
	int j;
	//计算正多边形的分割角度：
	GLfloat dtheta = 2.0f * pi / ((GLfloat)surfaceNum);
	GLfloat u = 0.0f;
	GLfloat v = 1.0f;
	GLfloat dv = 1.0 / height;
	GLfloat du = 1.0 / ((GLfloat)surfaceNum);


	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	glBegin(GL_TRIANGLE_STRIP);
	for (j = 0; j <= surfaceNum; j++)
	{
		GLfloat theta = (GLfloat)((j - 1 / 2) * dtheta);
		GLfloat costheta = (GLfloat)(cos(theta));
		GLfloat sintheta = (GLfloat)(sin(theta));

		GLfloat x = r*costheta;
		GLfloat y = r*sintheta;
		GLfloat z = 0;
		glTexCoord2f(u, 0.0f);
		glVertex3f(x, y, z);
		
		GLfloat ax = x;
		GLfloat ay = y;
		GLfloat az = height;
		glTexCoord2f(u, 1.0f);
		glVertex3f(ax, ay, az);
		u += du;
	}
	glEnd();

	//画顶面底面：
	DrawPolygon(surfaceNum, 0.0f, r, index);
	DrawPolygon(surfaceNum, height, r, index);
	glPopMatrix();

}

void TexturePainter::DrawPolygon(GLint surfaceNum, GLfloat zdata, GLfloat r, int index)
{
	int j;
	//计算正多边形的夹角角度：
	GLfloat dtheta = 2.0f * pi / ((GLfloat)surfaceNum);
	GLfloat u = 0.5f;
	GLfloat v = 0.5f;
	GLfloat du = 1.0 / ((GLfloat)surfaceNum);
	GLfloat dv = 1.0 / ((GLfloat)surfaceNum);

	glPushMatrix();
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	glBegin(GL_TRIANGLE_STRIP);
	for (j = 0; j <= surfaceNum; j++)
	{
		GLfloat theta = (GLfloat)(j * dtheta);
		GLfloat costheta = (GLfloat)(cos(theta));
		GLfloat sintheta = (GLfloat)(sin(theta));

		GLfloat x = r*costheta;
		GLfloat y = r*sintheta;
		GLfloat z = zdata;

		glTexCoord2f(u + costheta * 0.5, v + sintheta * 0.5);
		glVertex3f(x, y, z);

		glTexCoord2f(u, v);
		glVertex3f(0.0, 0.0, z);
		//u += du;
	}
	glEnd();
	glPopMatrix();

}

void TexturePainter::DrawCylinder(GLfloat r, GLfloat height, GLint longitude, GLint latitude, int index)
{
	GLfloat dtheta = 2.0f * (GLfloat)pi / (GLfloat)longitude;
	GLfloat dh = height / (GLfloat)latitude;
	GLfloat du = 1.0f / longitude;
	GLfloat dv = 1.0f / latitude;
	GLfloat u = 0.0f;
	GLfloat v = 1.0f;
	GLfloat x, y, z, ax, ay, az;
	GLint count = 0;
	GLint i, j;
	GLfloat dr = r / (GLfloat)latitude;

	glPushMatrix();
	//画侧面：
	if (index >= 0) glBindTexture(GL_TEXTURE_2D, texture[index]);
	for (i = 0; i<latitude; i++)
	{
		GLfloat h = (GLfloat)(i*dh);
		GLfloat aboveh = (GLfloat)(h + dh);

		glBegin(GL_TRIANGLE_STRIP);
		u = 0.0f;
		for (j = 0; j <= longitude; j++){

			GLfloat theta = (GLfloat)(j*dtheta);
			GLfloat sintheta = (GLfloat)(sin(theta));
			GLfloat costheta = (GLfloat)(cos(theta));

			x = costheta * r;
			y = sintheta * r;
			z = h;

			glTexCoord2f(u, v);
			glNormal3f(costheta, sintheta, 0);
			glVertex3f(x, y, z);

			//画同一经线上不同纬度的另外一点
			ax = costheta * r;
			ay = sintheta * r;
			az = aboveh;

			glTexCoord2f(u, v - dv);
			glNormal3f(costheta, sintheta, 0);
			glVertex3f(ax, ay, az);
			u += du;
		}
		glEnd();
		v -= dv;
	}
	glPopMatrix();
	//画顶面地面:
	DrawCircle(r, 0, latitude, longitude, false, index);
	DrawCircle(r, height, latitude, longitude, true, index);

}