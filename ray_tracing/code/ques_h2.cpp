#include <GL/glut.h>
#include "math.h"
#include <windows.h>
#include "material.h"
#include "object.h"
#include "light.h"
#include "render.h"
#include "plydecoder.h"
#include <stdlib.h> 
#include<stdio.h>  
#include <iostream>
using namespace std;
#define WINDOW_WIDTH  600  
#define WINDOW_HEIGHT 600  

void initScene()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void resizeGL(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

perspectiveCamera camera(GVector3(-50, 40, 10), GVector3(0.5, -0.4, -0.1), GVector3(0, 0, 1), 90);
objUnion scene;
lightUnion lights;

void rendScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);

	long maxDepth = 20;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	int total = WINDOW_WIDTH * WINDOW_HEIGHT;
	int count = 0;
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx*x;
			Ray ray(camera.generateRay(sx, sy));
			Color color = rend(ray, scene, lights, true, 3);
			glColor3ub(color.r * 255 > 255 ? 255 : color.r * 255,
				color.g * 255 > 255 ? 255 : color.g * 255,
				color.b * 255 > 255 ? 255 : color.b * 255);
			glVertex2f(sx, sy);
			count++;
			if (count % 1000 == 0) {
				cout << count << '/' << total << endl;
			}
		}
	}
	glEnd();
	glutSwapBuffers();
}

//Uncomment if you want to try animation rendering
/*
Material mComic1(Color::BlueViolet(), 0.0);
Material mComic2(Color::LightSkyBlue(), 0.7);
Sphere sphereComic(GVector3(-20, 0, -10), 7, &mComic1);
GVector3 oriCenter(0,0,-10);
GVector3 upCenter(0,0,1);
Plane planeComic = Plane(GVector3(0, 0, 1), -20.0, &mComic2);
PointLight lightComic1(Color::white(), 1000, GVector3(-10, 0, 10), true);
AmbientLight lightComic2(Color::white().multiply(0.1));
objUnion sceneComic;
lightUnion lightsComic;
GVector3 v;
GVector3 newC;

void rendComic() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	long maxDepth = 20;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);

	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx*x;
			Ray ray(camera.generateRay(sx, sy));

			Color color = rend(ray, sceneComic, lightsComic, true, 3);
			
			glColor3ub(color.r * 255 > 255 ? 255 : color.r * 255,
				color.g * 255 > 255 ? 255 : color.g * 255,
				color.b * 255 > 255 ? 255 : color.b * 255);
			glVertex2f(sx, sy);
		}
	}
	glEnd();
	glutSwapBuffers();
}

void TimeControl(GLint value) {
	v = sphereComic.getCenter() - oriCenter;
	newC = sphereComic.getCenter() + (v.crossMul(upCenter).normalize());
	newC = (newC.normalize()) * 20;
	sphereComic.setCenter(newC);
	rendComic();
	glutTimerFunc(33, TimeControl, 1);
}
*/
int main(int argc, char ** argv)
{
	//Uncomment if you want to try animation rendering
	/*
	sceneComic.push(&sphereComic);
	sceneComic.push(&planeComic);
	lightsComic.push(&lightComic1);
	lightsComic.push(&lightComic2);
	*/

	glutInit(&argc, argv);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Render");
	initScene();

	Material m1 = Material(Color::white(), 1.0);
	Material m2 = Material(Color::DarkOrange2(), 0.0);
	Material m3 = Material(Color(0.1,0.7,0.9), 0.3);
	Material m4 = Material(Color::white(), 0.0);
	Material m5 = Material(Color::LightSkyBlue(), 0.2);
	Material m6 = Material(Color::SpringGreen1(), 1.0);

	//Uncomment if you want to load ply model
	/*
	char *plyFile = "cat-2.ply\0";
	PLY model;
	cout << "load ply model" << endl;
	model.Load(plyFile,20, &m2);
	cout << "model loaded" << endl;
	for (int i = 0; i < model.faceNum; i++) {
	scene.push(model.faces + i);
	}
	*/
	
	Plane plane1 = Plane(GVector3(0, 0, 1), -20.0, &m5);
	Plane plane2 = Plane(GVector3(-1, 0, 0), -30.0, &m1);
	Plane plane3 = Plane(GVector3(0, 1, 0), -40.0, &m4);
	Sphere sphere1 = Sphere(GVector3(0, 0, 10), 10.0, &m2);
	Sphere sphere2 = Sphere(GVector3(0, 0, -10), 10.0, &m2);
	Sphere sphere3 = Sphere(GVector3(-25, 6, 0), 5.0, &m6);
	AmbientLight light3(Color::white().multiply(0.1));
	PointLight light1(Color::white(), 1000, GVector3(-70, 15, 10), true);
	PointLight light2(Color::white(), 800, GVector3(-10, 50, 10), true);
	scene.push(&sphere3);
	scene.push(&plane1);
	scene.push(&plane2);
	scene.push(&plane3);
	lights.push(&light1);
	lights.push(&light2);
	lights.push(&light3);
	
	glutReshapeFunc(resizeGL);
	glutDisplayFunc(rendScene);
	//Uncomment if you want to try animation rendering
	//glutTimerFunc(33, TimeControl, 1);
	//glutDisplayFunc(rendComic);
	glutMainLoop();
	return 0;
}