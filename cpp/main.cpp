#include "m_import.h"
#include "ModelPainter.h"

using namespace std;

static string FileAddress = "cube.obj";
GLint bPersp = 1;

float eye[] = {0, 0, 8};

void mykey(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 'w':
		eye[1]++;
		break;
	case 'a':
		eye[0]--;
		break;
	case 's':
		eye[1]--;
		break;
	case 'd':
		eye[0]++;
		break;
	case 'q':
		eye[2]--;
		break;
	case 'e':
		eye[2]++;
		break;
	}
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
	objImporter mImporter;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2],
		0.0 ,0.0, 0.0,
		0, 1, 0);	

	mImporter.ProcessFileInfo(FileAddress);
	mImporter.DrawObject();
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);                                                     
	int windowHandle = glutCreateWindow("Simple GLUT App");
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(mykey);		
	glutIdleFunc(idle);						
	
	glutMainLoop();
	return 0;
}