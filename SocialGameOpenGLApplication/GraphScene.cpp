#include "GraphScene.h"


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

typedef	GLdouble Vertice[3];

typedef struct GraphCamera{
	GLfloat height;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice eye;
	Vertice center;
}GraphCamera;

typedef struct Graphspecial_Key{
	GLboolean   up, down, left, right;
}Graphspecial_Key;

typedef struct GraphMouse_State{
	GLint        xMouse;
	GLint        yMouse;
}GraphMouse_State;


GraphCamera PersonCam;
GraphCamera MinimapCam;
Graphspecial_Key KeyStatus;
GraphMouse_State MouseStatus;

GraphScene::GraphScene(SocialGamePublicAPIClient * client, string loginEmail)
{
	onGame = false;
	apiClient = client;
	email = loginEmail;
	graph =	apiClient->getGraph(email,5);
	graphCoordWalker walker;
	walker.walk(graph);

	maxConnectionStrenght = walker.getMaxConnectionStrenght();
	maxUserConnections = walker.getMaxUserConnections();
}


GraphScene::~GraphScene()
{
}


void GraphScene::Draw(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CamLookAt();
	GraphWalkerDraw drawWalker(maxUserConnections, maxConnectionStrenght);
	drawWalker.walk(graph);

	if (onGame){
		gameScene->Draw();
	}

	glutSwapBuffers();
	glFlush();

}

void GraphScene::Init(void){
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
	glShadeModel(GL_SMOOTH);
	StartCam();
}

void GraphScene::subWindowInit(void){
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
	glShadeModel(GL_SMOOTH);
	StartCam();
}


void GraphScene::Timer(int value){
	if (onGame){
		gameScene->Timer(value);
		return;
	}
	
	
	if (KeyStatus.up){
		PersonCam.dist -= 0.01;
	}
	if (KeyStatus.down){
		PersonCam.dist += 0.01;
	}
	if (KeyStatus.left){
		PersonCam.dir_long += M_PI*0.001;
	}
	if (KeyStatus.right){
		PersonCam.dir_long -= M_PI*0.001;
	}
}

void GraphScene::Key(unsigned char key, int x, int y){
	if (onGame){
		gameScene->Key(key,x,y);
		return;
	}
	switch (key) {
	case 27:
		exit(1);
		break;
	case 'q':
	case 'Q':
		PersonCam.height += 0.1;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		PersonCam.height -= 0.1;
		glutPostRedisplay();
		break;
	}
}

void GraphScene::SpecialKey(int key, int x, int y){
	if (onGame){
		gameScene->SpecialKey(key,x,y);
		return;
	}
	
	switch (key){
	case GLUT_KEY_UP: KeyStatus.up = GL_TRUE;
		break;
	case GLUT_KEY_DOWN: KeyStatus.down = GL_TRUE;
		break;
	case GLUT_KEY_LEFT: KeyStatus.left = GL_TRUE;
		break;
	case GLUT_KEY_RIGHT: KeyStatus.right = GL_TRUE;
		break;
	}
}

void GraphScene::SpecialKeyUp(int key, int x, int y){
	if (onGame){
		gameScene->SpecialKeyUp(key,x,y);
		return;
	}
	
	switch (key) {
	case GLUT_KEY_UP: KeyStatus.up = GL_FALSE;
		break;
	case GLUT_KEY_DOWN: KeyStatus.down = GL_FALSE;
		break;
	case GLUT_KEY_LEFT: KeyStatus.left = GL_FALSE;
		break;
	case GLUT_KEY_RIGHT: KeyStatus.right = GL_FALSE;
		break;
	}
}

void GraphScene::drawSubWindow(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	TopCamLookAt();

	//draw subscene
	GraphWalkerDraw drawWalker(maxUserConnections, maxConnectionStrenght);
	drawWalker.walk(graph);

	glutSwapBuffers();
	glFlush();
}

bool GraphScene::isSubWindowActive(){
	return true;
}

void GraphScene::StartCam(){
	PersonCam.dir_lat = M_PI / 4;
	PersonCam.dir_long = -M_PI / 4;
	PersonCam.height = 0;
	PersonCam.dist = 40;
	PersonCam.center[0] = 0;
	PersonCam.center[1] = 0;
	PersonCam.center[2] = 0;
}

void GraphScene::CamLookAt(){
	
	PersonCam.eye[0] = PersonCam.center[0] + PersonCam.dist*cos(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.eye[1] = PersonCam.center[1] + PersonCam.dist*sin(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.eye[2] = PersonCam.center[2] + PersonCam.dist*sin(PersonCam.dir_lat);
	gluLookAt(
		PersonCam.eye[0], PersonCam.eye[1], PersonCam.eye[2] + PersonCam.height,
		PersonCam.center[0], PersonCam.center[1], PersonCam.center[2] + PersonCam.height,
		0, 0, 1
		);
}

void GraphScene::TopCamLookAt(){
	MinimapCam.eye[0] = PersonCam.center[0];
	MinimapCam.eye[1] = PersonCam.center[1];
	MinimapCam.eye[2] = 50;
	gluLookAt(
		MinimapCam.eye[0], MinimapCam.eye[1], MinimapCam.eye[2],
		PersonCam.center[0], PersonCam.center[1], PersonCam.center[2],
		0, 1, 0
		);
}

void GraphScene::MotionMouse(int x, int y)
{
	float newx = RAD((MouseStatus.xMouse - x)*0.1);
	float newy = RAD((MouseStatus.yMouse - y)*0.1);
	GLdouble latitude;
	GLdouble longitude;
	longitude = PersonCam.dir_long - newx;
	latitude = PersonCam.dir_lat;
	//if (PersonCam.dir_lat - newy < M_PI / 4 && PersonCam.dir_lat - newy > -M_PI / 4)
	latitude += newy;
	PersonCam.center[0] = PersonCam.eye[0] - PersonCam.dist*cos(longitude)*cos(latitude);
	PersonCam.center[1] = PersonCam.eye[1] - PersonCam.dist*sin(longitude)*cos(latitude);
	PersonCam.center[2] = PersonCam.eye[2] - PersonCam.dist*sin(latitude);
	MouseStatus.xMouse = x;
	MouseStatus.yMouse = y;
}

void GraphScene::Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			MouseStatus.xMouse = x;
			MouseStatus.yMouse = y;
			glutMotionFunc(GraphOpenGL::MotionMouse);

		}
		else{
			glutMotionFunc(NULL);
		}
	}
}
