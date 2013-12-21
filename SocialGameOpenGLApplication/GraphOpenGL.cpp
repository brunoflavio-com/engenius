#include "GraphOpenGL.h"
#include "GraphScene.h"

#define GAP		25

typedef struct GraphWindows{
	GLint        Main;
	GLint        Top;
}GraphWindows;

GraphWindows Window;


GraphOpenGL::GraphOpenGL(){
}

InterfaceScene * GraphOpenGL::graphScene;
SubWindowSceneInterface *GraphOpenGL::subgraphScene;


GraphOpenGL::~GraphOpenGL(){}


void GraphOpenGL::Init(){
	graphScene->Init();
}

void GraphOpenGL::MotionMouse(int x, int y)
{
	graphScene->MotionMouse(x,y);
}

void GraphOpenGL::Mouse(int button, int state, int x, int y){
	graphScene->Mouse(button,state,x, y);
}

void GraphOpenGL::ReshapeMinimap(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble)width / height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GraphOpenGL::Reshape(int width, int height){
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble)width / height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GraphOpenGL::DrawMinimap(){
	subgraphScene->drawSubWindow();
}

void GraphOpenGL::Draw(){
	graphScene->Draw();
	
}

void GraphOpenGL::redisplayAll(void)
{
	glutSetWindow(Window.Main);
	glutPostRedisplay();
	glutSetWindow(Window.Top);
	
	if (subgraphScene->isSubWindowActive()){
		glutShowWindow();
	}
	else{
		glutHideWindow();
	}

	glutPostRedisplay();
}

void GraphOpenGL::Timer(int value){
	glutTimerFunc(1, Timer, 0);
	graphScene->Timer(value);
	//glutPostRedisplay();
	redisplayAll();
}

void GraphOpenGL::PrintKeys(){
	printf("Up/Down - Zoom in/out\n");
	printf("Left/Right - rodar para a esquerda/direita\n");
	printf("Q/q/A/a - subir/descer\n");
	printf("ESC - Sair\n");
}

void GraphOpenGL::Key(unsigned char key, int x, int y){

	graphScene->Key(key,x, y);
}

void GraphOpenGL::SpecialKey(int key, int x, int y){
	graphScene->SpecialKey(key, x, y);
}

void GraphOpenGL::SpecialKeyUp(int key, int x, int y){
	graphScene->SpecialKeyUp(key, x, y);
}

void GraphOpenGL::Run(int argc, char **argv, InterfaceScene * scene, SubWindowSceneInterface * subWindowScene)
{
	graphScene = scene;
	subgraphScene = subWindowScene;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800 + GAP * 3, 400 + GAP * 2);
	if ((Window.Main = glutCreateWindow("Grafo Social")) == GL_FALSE)
		exit(1);
	PrintKeys();

	//Main window
	graphScene->Init();
	glutTimerFunc(1, Timer, 0);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMouseFunc(Mouse);

	//Minimap Subwindow
	
	Window.Top = glutCreateSubWindow(Window.Main, GAP, GAP, 200, 200);
	subgraphScene->subWindowInit();
	glutTimerFunc(1, Timer, 0);
	glutReshapeFunc(ReshapeMinimap);
	glutDisplayFunc(DrawMinimap);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMouseFunc(Mouse);
	glutMainLoop();
	
}