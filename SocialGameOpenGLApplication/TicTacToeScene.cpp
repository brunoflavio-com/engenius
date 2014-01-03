#include "TicTacToeScene.h"
#include <gl\freeglut.h>
#include <ctype.h>

#define PI 3.14159265358979323846


TicTacToeScene::TicTacToeScene()
{
	//initialize game engine:
	game = new TicTacToePLEngine('o');
	//for test
	this->board[0] = 'h';
	this->board[1] = 'c';
	this->board[8] = 'h';
}


TicTacToeScene::~TicTacToeScene()
{
	if (game != NULL)
	{
		delete game;
	}
}


//Initiate Scene
void TicTacToeScene::Init(void){

}

// Timer Callback
void TicTacToeScene::Timer(int value)
{
	
}

// Draw Callback
void TicTacToeScene::Draw(void)
{
	
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	

	// Define a viewing transformation
	gluLookAt(0.0, -1.5, 8, 1.5, -1.5, 0, 0, 1, 0);
	
	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others
	glPushMatrix(); //Save the transformations performed thus far
		
	drawBoard();
		
	//Draw the game engine message:
	glPushMatrix();
	unsigned char msg[100];
	strcpy((char*) msg, game->getMessage().c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, msg);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	glPopMatrix();

	glutSwapBuffers();//Send the 3D scene to the screen
}


// Keyboard callback
void TicTacToeScene::Key(unsigned char key, int x, int y) //The key that was pressed, and the current mouse coordenates
{
	switch (key) {

	
	case 27:
		//end game on ESC?
		break;
	}

	//pass letters to the game engine:
	if (isalpha(key))
	{
		/*game->play(key);*/
	}
}

// Special key callback
void TicTacToeScene::SpecialKey(int key, int x, int y)
{

}

// Special key UP callback
void TicTacToeScene::SpecialKeyUp(int key, int x, int y)
{

}

// Mouse Callbacks
void TicTacToeScene::Mouse(int btn, int state, int x, int y)
{

}

void TicTacToeScene::MotionMouse(int x, int y)
{

}


void TicTacToeScene::drawGrid(void)
{
	//Cilinder height
	float h = 3.0f;
	//Draw Grid
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	//translate...

	glPushMatrix();
	glTranslatef(1.0, 0, 0);
	glutSolidCylinder(0.1f, h, 10, 10);
	glTranslatef(1.0, 0, 0);
	glutSolidCylinder(0.1f, h, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(h, 0.0f, 0.0f);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(1.0, 0, 0);
	glutSolidCylinder(0.1f, h, 10, 10);
	glTranslatef(1.0, 0, 0);
	glutSolidCylinder(0.1f, h, 10, 10);
	glPopMatrix();

	glPopMatrix();

}

void TicTacToeScene::drawX(float x, float y)
{
	float w = 1.0f;
	float h = sqrt((w*w) * 2.0f);

	glPushMatrix();
	glTranslatef(w / -2.0, w / 2.0, 0.0f);
	glTranslatef(x, y, 0.0f);
	glRotatef(90, 1.0f,0.0f, 0.0f);

		glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glutSolidCylinder(0.1f, h, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(w, 0.0f, 0.0f);
		glRotatef(-45, 0.0f, 1.0f, 0.0f);
		glutSolidCylinder(0.1f, h, 10, 10);
		glPopMatrix();

	glPopMatrix();

}

void TicTacToeScene::drawO(float x, float y)
{
	float r = 0.5f;
	int n = 20;
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glutSolidSphere(r, n, n);
	glPopMatrix();


}

void TicTacToeScene::drawBoard(){
		drawGrid();
		//Square1
		if (board[0] == 'c')
			drawX(0.5f, -0.5f);
		else if (board[0] == 'h')
			drawO(0.5f, -0.5f);
		//Square2
		if (board[1] == 'c')
			drawX(1.5f, -0.5f);
		else if (board[1] == 'h')
			drawO(1.5f, -0.5f);
		//Square3
		if (board[2] == 'c')
			drawX(2.5f, -0.5f);
		else if (board[2] == 'h')
			drawO(2.5f, -0.5f);
		//Square4
		if (board[3] == 'c')
			drawX(0.50f, -1.5f);
		else if (board[3] == 'h')
			drawO(0.50f, -1.5f);
		//Square5
		if (board[4] == 'c')
			drawX(1.50f, -1.5f);
		else if (board[4] == 'h')
			drawO(1.50f, -1.5f);
		//Square6
		if (board[5] == 'c')
			drawX(2.50f, -1.5f);
		else if (board[5] == 'h')
			drawO(2.50f, -1.5f);
		//Square7
		if (board[6] == 'c')
			drawX(0.50f, -2.5f);
		else if (board[6] == 'h')
			drawO(0.50f, -2.5f);
		//Square8
		if (board[7] == 'c')
			drawX(1.50f, -2.5f);
		else if (board[7] == 'h')
			drawO(1.50f, -2.5f);
		//Square9
		if (board[8] == 'c')
			drawX(2.50f, -2.5f);
		else if (board[8] == 'h')
			drawO(2.50f, -2.5f);
		glFlush();
	}
