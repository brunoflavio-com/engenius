#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#ifndef IGL_H
#include "interfaceGL.h"
#endif

//#include "interfaceGL.h"
//#include "teste3.h"
//InterfaceGL * jogoAtual;
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
	jogoAtual->Run(argc, argv);
	
	
	/*glutGameModeString("1024x768:32@75");
	// 1º teste
	if
		(glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
		glutEnterGameMode();
	else
	{
		glutGameModeString("800x600:32@60");
		// 2º teste
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
	printf("testeR");
}

