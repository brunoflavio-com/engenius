#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include "GrafoStructs.h"

Camera PersonCam;
Camera MinimapCam;
special_Key KeyStatus;
Mouse_State MouseStatus;
Windows Window;

void StartCam(){
	PersonCam.dir_lat = M_PI/4;
	PersonCam.dir_long = -M_PI/4;
	PersonCam.height = 0;
	PersonCam.dist = 10;
	PersonCam.center[0] = 0;
	PersonCam.center[1] = 0;
	PersonCam.center[2] = 0;
}

void CamLookAt(){
	PersonCam.eye[0]=PersonCam.center[0]+PersonCam.dist*cos(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.eye[1]=PersonCam.center[1]+PersonCam.dist*sin(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.eye[2]=PersonCam.center[2]+PersonCam.dist*sin(PersonCam.dir_lat);
	gluLookAt(
		PersonCam.eye[0],PersonCam.eye[1],PersonCam.eye[2]+PersonCam.height,
		PersonCam.center[0],PersonCam.center[1],PersonCam.center[2]+PersonCam.height,
		0,0,1
		);
}

void TopCamLookAt(){
	MinimapCam.eye[0]=PersonCam.eye[0];
	MinimapCam.eye[1]=PersonCam.eye[1];
	MinimapCam.eye[2]=50;
	gluLookAt(
		MinimapCam.eye[0],MinimapCam.eye[1],MinimapCam.eye[2],
		PersonCam.eye[0],PersonCam.eye[1],PersonCam.eye[2],
		0,1,0
		);
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

void MotionMouse(int x, int y)
{
	float newx = RAD(MouseStatus.xMouse - x);
	float newy = RAD(MouseStatus.yMouse - y);
	PersonCam.dir_long += newx;
	if(PersonCam.dir_lat - newy < M_PI/4 && PersonCam.dir_lat - newy > -M_PI/4)
		PersonCam.dir_lat -= newy;
	MouseStatus.xMouse = x;
	MouseStatus.yMouse = y;
}

void Mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			MouseStatus.xMouse = x;
			MouseStatus.yMouse = y;
			glutMotionFunc(MotionMouse);

		} else{
			glutMotionFunc(NULL);
		}
	}
}

void ReshapeMinimap(int width, int height)
{
	glViewport(0, 0, (GLint) width, (GLint) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective( 65.0, (GLdouble) width / height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Reshape(int width, int height){
	glViewport(0, 0, (GLint) width, (GLint) height);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 65.0, (GLdouble) width / height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DrawMinimap(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	TopCamLookAt();

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

void redisplayAll(void)
{
	glutSetWindow(Window.Main);
    glutPostRedisplay();
    glutSetWindow(Window.Top);
    glutPostRedisplay();
}

void Timer(int value){
	glutTimerFunc(1,Timer,0);
	if(KeyStatus.up){
		PersonCam.dist-=0.01;
	}
	if(KeyStatus.down){
		PersonCam.dist+=0.01;
	}
	if(KeyStatus.left){
		PersonCam.dir_long+=M_PI*0.001;
	}
	if(KeyStatus.right){
		PersonCam.dir_long-=M_PI*0.001;
	}
	//glutPostRedisplay();
	redisplayAll();
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
	case 'q':
	case 'Q':
		PersonCam.height+=0.1;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		PersonCam.height-=0.1;
		glutPostRedisplay();
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
	int WindowsStatus;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800+GAP*3, 400+GAP*2);
	if ((Window.Main=glutCreateWindow("Grafo Social")) == GL_FALSE)
	    exit(1);
	PrintKeys();
	
	//Main window
	Init();
	glutTimerFunc(1,Timer,0);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMouseFunc(Mouse);
	
	//Minimap Subwindow
	Window.Top = glutCreateSubWindow(Window.Main, GAP, GAP, 200, 200);
	Init();
	glutTimerFunc(1,Timer,0);
	glutReshapeFunc(ReshapeMinimap);
	glutDisplayFunc(DrawMinimap);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMouseFunc(Mouse);
	glutMainLoop();
}