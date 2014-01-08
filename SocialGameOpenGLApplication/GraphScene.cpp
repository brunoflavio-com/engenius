#include "GraphScene.h"
#include "HangmanScene.h"
#include "GraphFactory.h"


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define BUFFSIZE 512
GLuint selecter[BUFFSIZE];
ISelectable * selectedObject = NULL;

typedef	GLdouble Vertice[3];

typedef struct GraphCamera{
	GLfloat height;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	GLfloat vel;
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
}


GraphScene::~GraphScene()
{
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

void GraphScene::CamMovement(void){
	GLdouble z = PersonCam.eye[2] + PersonCam.vel*sin(PersonCam.dir_lat);
	GLdouble y = PersonCam.eye[1] + PersonCam.vel*sin(PersonCam.dir_long);
	GLdouble x = PersonCam.eye[0] + PersonCam.vel*cos(PersonCam.dir_long);
	PersonCam.eye[0] = x;
	PersonCam.eye[1] = y;
	PersonCam.eye[2] = z;
}


void GraphScene::Timer(int value){
	if (KeyStatus.up){
		PersonCam.vel = 0.01;
		CamMovement();
	}
	if (KeyStatus.down){
		PersonCam.vel = -0.01;
		CamMovement();
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
	PersonCam.dir_lat = -M_PI/4;
	PersonCam.dir_long = -M_PI/4;
	PersonCam.height = 0;
	PersonCam.dist = 40;
	PersonCam.center[0] = 0;
	PersonCam.center[1] = 0;
	PersonCam.center[2] = 0;
	PersonCam.eye[0] = PersonCam.center[0] - PersonCam.dist*cos(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.eye[1] = PersonCam.center[1] - PersonCam.dist*sin(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.eye[2] = PersonCam.center[2] - PersonCam.dist*sin(PersonCam.dir_lat);
	gluLookAt(
		PersonCam.eye[0], PersonCam.eye[1], PersonCam.eye[2] + PersonCam.height,
		PersonCam.center[0], PersonCam.center[1], PersonCam.center[2] + PersonCam.height,
		0, 0, 1
		);
}

void GraphScene::CamLookAt(){
	
	PersonCam.center[0] = PersonCam.eye[0] + PersonCam.dist*cos(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.center[1] = PersonCam.eye[1] + PersonCam.dist*sin(PersonCam.dir_long)*cos(PersonCam.dir_lat);
	PersonCam.center[2] = PersonCam.eye[2] + PersonCam.dist*sin(PersonCam.dir_lat);
	gluLookAt(
		PersonCam.eye[0], PersonCam.eye[1], PersonCam.eye[2] + PersonCam.height,
		PersonCam.center[0], PersonCam.center[1], PersonCam.center[2] + PersonCam.height,
		0, 0, 1
		);
}

void GraphScene::TopCamLookAt(){
	MinimapCam.eye[0] = 0;
	MinimapCam.eye[1] = 0;
	MinimapCam.eye[2] = 50;
	gluLookAt(
		MinimapCam.eye[0], MinimapCam.eye[1], MinimapCam.eye[2],
		0, 0, 0,
		0, 1, 0
		);
}

void GraphScene::PassiveMotion(int newx, int newy){
	ISelectable * object;
	if (selectedObject != NULL)
		selectedObject->selected = false;

	if ((object = pickISelectable(newx, newy)) != NULL ) {
		selectedObject = object;
		selectedObject->selected = true;
	}

	glutPostRedisplay();
}

ISelectable * GraphScene::pickISelectable(int newx, int newy) {
	GLint viewport[4];
	GLint hits;

	(void)glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(-1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(newx, glutGet(GLUT_WINDOW_HEIGHT) - newy, 5.0, 5.0, viewport); // searches for existing items on the path
	gluPerspective(65.0, (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	Draw3dObjects();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);

	if (hits > 0) {
	    // if glut detects items, gets the name
		GLuint depth = (GLuint)~0;
		unsigned int getThisName;
		GLint i;
		GLuint names, pos, *ptr;
		GLuint selectableObjectType = -1, selectableObjectId =-1;

		ptr = (GLuint *)selecter;
		
		for (i = 0; i < hits; i++) {
			getThisName = 0;
			names = *ptr;
			ptr++;

			//ZMIN
			if (*ptr <= depth) {
				depth = *ptr;
				getThisName = 1;
			}

			ptr++;
			//ZMAX
			ptr++;

			if (getThisName){
				selectableObjectType = *ptr;
				++ptr;
				selectableObjectId = *ptr;
				++ptr;
			}
			else{
				ptr += 2;
			}
		}
		
		switch (selectableObjectType)
		{
		case ISelectable::USER_TYPE:
			//User
			if (selectableObjectId < graph->users.size() ){
				 return (ISelectable*)graph->users.at(selectableObjectId);
			}

			break;
		case ISelectable::RELATIONSHIP_TYPE:
			//Reference
			if (selectableObjectId < graph->relationShips.size()){
				return (ISelectable*)graph->relationShips.at(selectableObjectId);
			}
			break;
		}
		
	}
	return NULL;
}

void GraphScene::MotionMouse(int x, int y)
{
	int dif;
	dif = y - MouseStatus.yMouse;
	if (dif > 0){//looking down
		PersonCam.dir_lat -= dif*RAD(1);
		if (PersonCam.dir_lat < -RAD(89))
			PersonCam.dir_lat = -RAD(89);
	}
	if (dif < 0){//looking up
		PersonCam.dir_lat += abs(dif)*RAD(1);
		if (PersonCam.dir_lat > RAD(89))
			PersonCam.dir_lat = RAD(89);
	}

	dif = x - MouseStatus.xMouse;
	if (dif > 0){//looking right
		PersonCam.dir_long -= dif*RAD(1);
	}
	if (dif < 0){//looking left
		PersonCam.dir_long += abs(dif)*RAD(1);
	}

	MouseStatus.xMouse = x;
	MouseStatus.yMouse = y;
}

void GraphScene::Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			MouseStatus.xMouse = x;
			MouseStatus.yMouse = y;
			glutMotionFunc(GraphOpenGL::MotionMouse);

			ISelectable * object;			
			if ((object = pickISelectable(x, y)) != NULL) {
				User * user = (User *)object;

				moveGraphToNewUser(user);

				
			}

		}
		else{
			glutMotionFunc(NULL);
		}
	}
}
