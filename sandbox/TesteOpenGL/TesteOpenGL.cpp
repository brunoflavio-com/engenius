#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "interfaceGL.h"
InterfaceGL * jogoAtual[3];
#include "teste.h"
#include "Cubo.h"
#include "Main.h"



void main(int argc, char **argv)
{
	jogoAtual[3] = new InterfaceGL();
	jogoAtual[0] = new Main();
	jogoAtual[1] = new Cubo();
	jogoAtual[2] = new Teste();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
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
	jogoAtual[0]->Run();
	glutMainLoop();
}

