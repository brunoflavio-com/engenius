#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "interfaceGL.h"
#include "teste.h"
#include "Cubo.h"

InterfaceGL * jogoAtual;

/*void Timer(int t) {
	glutTimerFunc(estado.delay, Timer, 0);
	jogoAtual->Timer(t);
}

void Reshape(int width, int height) {
	jogoAtual->Reshape(width,height);
}
void Draw(void) {
	jogoAtual->Draw();
}
void Key(unsigned char key, int x, int y) {
	jogoAtual->Key(key,x,y);
}*/

void main(int argc, char **argv)
{
	jogoAtual = new Cubo();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
	jogoAtual->Run();
	
	
	/*glutGameModeString("1024x768:32@75");
	// 1� teste
	if
		(glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
		glutEnterGameMode();
	else
	{
		glutGameModeString("800x600:32@60");
		// 2� teste
		if
			(glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			glutEnterGameMode();
		else
			// Cria Janela Normal
		{
			glutInitWindowPosition(10, 10);
			glutInitWindowSize(800, 600);
			glutCreateWindow("OpenGL");
		}
	}*/
	
	/*jogoAtual->Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutTimerFunc(estado.delay, Timer, 0);*/
		printf("teste22324234234");
	glutMainLoop();

	jogoAtual = new Teste2();
	jogoAtual->Run();
	glutMainLoop();

	while(1){
	printf("testeR");
	}
}

