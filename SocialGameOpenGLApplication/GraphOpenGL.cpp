#include "GraphOpenGL.h"
#include "AdvanceModeGraphScene.h"
#include "NormalModeGraphScene.h"


#define GAP		25

typedef struct GraphWindows{
	GLint        Main;
	GLint        Top;
}GraphWindows;

GraphWindows Window;

GraphOpenGL::GraphOpenGL(){
}

GraphScene * GraphOpenGL::advanceScene;
GraphScene  * GraphOpenGL::normalScene;
GraphScene * GraphOpenGL::currentScene;

bool GraphOpenGL::advancedMode = true;

GraphOpenGL::~GraphOpenGL(){
	delete advanceScene;
}

void GraphOpenGL::Init(){
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
	
	currentScene->Init();

}

void GraphOpenGL::InitTextures(){
	AUX_RGBImageRec *imagemBMP;
	imagemBMP = auxDIBImageLoad("./images/Textura.bmp");
	glBindTexture(GL_TEXTURE_2D, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imagemBMP->sizeX, imagemBMP->sizeY, GL_RGB, GL_UNSIGNED_BYTE, imagemBMP->data);
	glDisable(GL_TEXTURE_2D);
}
	

void GraphOpenGL::subWindowInit(){
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
	currentScene->subWindowInit();
}

void GraphOpenGL::MotionMouse(int x, int y)
{
	currentScene->MotionMouse(x, y);
}

void GraphOpenGL::Mouse(int button, int state, int x, int y){
	currentScene->Mouse(button, state, x, y);
}

void GraphOpenGL::PassiveMotion(int x, int y)
{
	currentScene->PassiveMotion(x, y);
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
	currentScene->drawSubWindow();
}

void GraphOpenGL::Draw(){
	currentScene->Draw();
	
}

void GraphOpenGL::redisplayAll(void)
{
	glutSetWindow(Window.Main);
	glutPostRedisplay();
	glutSetWindow(Window.Top);
	
	if (currentScene->isSubWindowActive()){
		glutShowWindow();
	}
	else{
		glutHideWindow();
	}

	glutPostRedisplay();
}

void GraphOpenGL::Timer(int value){
	if (!advancedMode && currentScene->isFinished){
		advanceScene->userLevel = normalScene->userLevel;
		advanceScene->userPoints = normalScene->userPoints;
		currentScene = advanceScene;
		currentScene->returningToGame = true;
		currentScene->returningMessage = normalScene->returningMessage;
		delete normalScene;
		advancedMode = true;
		ALuint buffer, source;
		buffer = alutCreateBufferFromFile("./sounds/crowdcheer.wav");
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, buffer);
		alSourcePlay(source);
		currentScene->createMessage("Congratulations you have achived yor mission");
	}
	currentScene->Timer(value);
	redisplayAll();
	glutTimerFunc(20, Timer, 0);

}


void GraphOpenGL::PrintKeys(){
	
	printf("Up/Down - Zoom in/out\n");
	printf("Left/Right - rodar para a esquerda/direita\n");
	printf("Q/q/A/a - subir/descer\n");
	printf("ESC - Sair\n");
}

void GraphOpenGL::Key(unsigned char key, int x, int y){
	if (key == 'c'){
		//Start Mission
			normalScene = new NormalModeGraphScene(advanceScene->apiClient, advanceScene->email, advanceScene->userLevel);
			normalScene->userLevel = advanceScene->userLevel;
			normalScene->userPoints = advanceScene->userPoints;
			currentScene = normalScene;
			currentScene->returningToGame = true;
			advancedMode = false;
		}
	currentScene->Key(key, x, y);
}

void GraphOpenGL::SpecialKey(int key, int x, int y){
	currentScene->SpecialKey(key, x, y);
}

void GraphOpenGL::SpecialKeyUp(int key, int x, int y){
	currentScene->SpecialKeyUp(key, x, y);
}

void GraphOpenGL::Run(int argc, char **argv, SocialGamePublicAPIClient * client, std::string email)
{
	advanceScene = new AdvanceModeGraphScene(client, email);
	currentScene = advanceScene;
	advancedMode = true;
	glutInit(&argc, argv);
	alutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800 + GAP * 3, 400 + GAP * 2);
	if ((Window.Main = glutCreateWindow("Grafo Social")) == GL_FALSE)
		exit(1);
	PrintKeys();

	//Main window
	Init();
	InitTextures();
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glutTimerFunc(20, Timer, 0);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(PassiveMotion);

	//Minimap Subwindow
	
	Window.Top = glutCreateSubWindow(Window.Main, GAP, GAP, 200, 200);
	subWindowInit();
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glutTimerFunc(20, Timer, 0);
	glutReshapeFunc(ReshapeMinimap);
	glutDisplayFunc(DrawMinimap);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutMouseFunc(Mouse);
	glutMainLoop();
	
}