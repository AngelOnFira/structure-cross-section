#include <windows.h>
#include <math.h>
#include "main.h"

#include <chrono>
#include <thread>

#define PI 3.1415926535897932384626433832795

#define WIDTH 640
#define HEIGHT 480

void init();
void reshape(int, int);
void display();

Structure* placenta;
static int radius = 2;

int main(int argc, char **argv)
{
	srand(static_cast <unsigned> (time(0)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("Structure");

	init();

	placenta = new Structure();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//Camera direction
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();

	glColor3f(0.2, 0.3, 0.5);

	placenta->draw();

	glPopMatrix();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	

	std::this_thread::sleep_for(std::chrono::milliseconds(25));
	glutPostRedisplay();
}