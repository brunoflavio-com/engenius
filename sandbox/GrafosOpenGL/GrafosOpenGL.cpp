#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include "GrafoStructs.h"

void Init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);
glShadeModel (GL_SMOOTH);
	/*glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  glPolygonMode(GL_BACK, GL_LINE);*/
}

void Reshape(int width, int height){
	glViewport(0, 0, (GLint) width, (GLint) height);  
  glMatrixMode(GL_PROJECTION);

  if (width < height)
     glOrtho(-5, 5, -5*(GLdouble)height/width, 5*(GLdouble)height/width,-10,10);
  else
     glOrtho(-5*(GLdouble)width/height, 5*(GLdouble)width/height,-5, 5, -10,10);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glBegin(GL_POLYGON);
	GLUquadricObj *quadric;
	glColor3f(1,0,0);
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL );
	gluSphere(quadric,1,30,10);
	glTranslatef(2,0,2);
	glColor3f(0,0,1);
	gluSphere(quadric,1,30,10);
	gluCylinder(quadric,.5,.5,2,30,10);
	glEnd();
	glutSwapBuffers();
	glFlush();
	
	glPopMatrix();
}

void Timer(int value){
	glutTimerFunc(1,Timer,0);
}

void PrintKeys(){
}

void Key(){
}

void SpecialKey(){
}

void SpecialKeyUp(){
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Grafo Social");
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutTimerFunc(1,Timer,0);
	glutMainLoop();
}