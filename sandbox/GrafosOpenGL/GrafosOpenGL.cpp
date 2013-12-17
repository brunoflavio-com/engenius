#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include "GrafoStructs.h"

Camera cam;
special_Key KeyStatus;

void StartCam(){
	cam.dir_lat = M_PI/4;
	cam.dir_long = -M_PI/4;
	cam.fov = 0;
	cam.dist = 10;
	cam.center[0] = 0;
	cam.center[1] = 0;
	cam.center[2] = 0;
}

void CamLookAt(){
	Vertice eye;
	eye[0]=cam.center[0]+cam.dist*cos(cam.dir_long)*cos(cam.dir_lat);
	eye[1]=cam.center[1]+cam.dist*sin(cam.dir_long)*cos(cam.dir_lat);
	eye[2]=cam.center[2]+cam.dist*sin(cam.dir_lat);
	gluLookAt(eye[0],eye[1],eye[2],cam.center[0],cam.center[1],cam.center[2],0,0,1);
}
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
	StartCam();
}

void Reshape(int width, int height){
	glViewport(0, 0, (GLint) width, (GLint) height);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 65.0, (GLdouble) width / height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CamLookAt();

	glBegin(GL_POLYGON);

	GLUquadricObj *quadric;
	glColor3f(1,0,0);
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL );
	gluSphere(quadric,1,30,10);
	glTranslatef(2,0,2);
	glColor3f(0,0,1);
	gluSphere(quadric,1,30,10);
	glRotatef(-135,0,1,0);
	gluCylinder(quadric,.5,.5,2,30,10);

	glEnd();

	glutSwapBuffers();
	glFlush();
}

void Timer(int value){
	glutTimerFunc(1,Timer,0);
	if(KeyStatus.up){
		cam.dist-=0.01;
	}
	if(KeyStatus.down){
		cam.dist+=0.01;
	}
	if(KeyStatus.left){
		cam.dir_long+=M_PI*0.001;
	}
	if(KeyStatus.right){
		cam.dir_long-=M_PI*0.001;
	}
	glutPostRedisplay();
}

void PrintKeys(){
	printf("Up/Down - Zoom in/out\n");
	printf("Left/Right - rodar para a esquerda/direita\n");
	printf("Q/q/A/a - subir/descer\n");
	printf("ESC - Sair\n");
}

void Key(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(1);
		break;
	}
}

void SpecialKey(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP: KeyStatus.up =GL_TRUE;
		break;
	case GLUT_KEY_DOWN: KeyStatus.down =GL_TRUE;
		break;
	case GLUT_KEY_LEFT: KeyStatus.left =GL_TRUE;
		break;
	case GLUT_KEY_RIGHT: KeyStatus.right =GL_TRUE;
		break;
	}
}

void SpecialKeyUp(int key, int x, int y){
	switch (key) {
	case GLUT_KEY_UP: KeyStatus.up =GL_FALSE;
		break;
	case GLUT_KEY_DOWN: KeyStatus.down =GL_FALSE;
		break;
	case GLUT_KEY_LEFT: KeyStatus.left =GL_FALSE;
		break;
	case GLUT_KEY_RIGHT: KeyStatus.right =GL_FALSE;
		break;
	}
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Grafo Social");
	PrintKeys();
	Init();
	glutTimerFunc(1,Timer,0);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMainLoop();
}