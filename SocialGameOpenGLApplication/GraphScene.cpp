#include "GraphScene.h"
#include "HangmanScene.h"


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define BUFFSIZE 512
GLuint selecter[BUFFSIZE];
GLuint theObject;

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
	apiClient = client;
	email = loginEmail;
	ns5__Graph * ns5_graph = apiClient->getGraph(email, 5);
	graph = new Graph(ns5_graph, loginEmail);
}


GraphScene::~GraphScene()
{
}

void GraphScene::myortho(void){
	GLfloat W = glutGet(GLUT_WINDOW_WIDTH);
	GLfloat H = glutGet(GLUT_WINDOW_HEIGHT);
	if (W <= H)
		glOrtho(-2.5, 2.5, -2.5 * H / W,
		2.5 * H / W, -100.0, 100.0);
	else
		glOrtho(-2.5 * W / H,
		2.5 * W / H, -2.5, 2.5, -100.0, 100.0);
}

void GraphScene::Draw(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CamLookAt();
	
	Draw3dObjects();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	DrawOverlay();

	glPopAttrib();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glutSwapBuffers();
	glFlush();

}

void GraphScene::Init(void){
	glShadeModel(GL_SMOOTH);
	glSelectBuffer(BUFFSIZE, selecter);
	StartCam();
}

void GraphScene::subWindowInit(void){
	
	StartCam();
}


void GraphScene::Timer(int value){
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
	graph->draw(false);
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

void GraphScene::PassiveMotion(int newx, int newy){
	GLint viewport[4];
	GLint hits;

	(void)glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(-1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	viewport[0] = 0;
	viewport[1] = 0;
	viewport[2] = glutGet(GLUT_WINDOW_WIDTH);
	viewport[3] = glutGet(GLUT_WINDOW_HEIGHT);
	gluPickMatrix(newx, viewport[3] - newy, 5.0, 5.0, viewport); // searches for existing items on the path
	myortho();
	glMatrixMode(GL_MODELVIEW);
	Draw();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);
	printf("Hits %d", hits);
	if (hits == 0)
		theObject = 0;
	else{ // if glut detects items, gets the name
		GLuint depth = (GLuint)~0;
		unsigned int getThisName;
		GLint i;
		GLuint names, *ptr;
		GLuint newObject;

		ptr = (GLuint *)selecter;
		newObject = 0;
		for (i = 0; i < hits; i++) {
			getThisName = 0;
			names = *ptr;
			ptr++;
			if (*ptr <= depth) {
				depth = *ptr;
				getThisName = 1;
			}
			ptr++;
			if (*ptr <= depth) {
				depth = *ptr;
				getThisName = 1;
			}
			ptr++;

			if (getThisName)
				newObject = *ptr;

			for (int i = 0; i < names; ++i) {
				if (*ptr > 0) {
					User * selectedUser = (User*) *ptr;
					printf(", %s", selectedUser->email.c_str());
				}
				ptr++;
			}

			//ptr += names;  
		}
		if (theObject != newObject) {
			theObject = newObject;		
			// TODO: set user as selected:
			// User * user = (User*)newObject;
			// user->selected = true;

			glutPostRedisplay();
		}
	}
	printf(".\n");
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
