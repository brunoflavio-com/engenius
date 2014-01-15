#include "TicTacToeScene.h"
#include <gl\freeglut.h>
#include <ctype.h>

#define PI 3.14159265358979323846

TicTacToeScene::TicTacToeScene(SocialGamePublicAPIClient *client, string loginEmail)
{
	//If necessary, use the client soap connection to get game related data from the server.
	//client->

	//initialize game engine:
	game = new TicTacToePLEngine('o');

	//initialize board (0 is empty)
	for (int i = 0; i < 9; i++) board[i] = 0;

	this->gameover = false;
	this->winner = false;
	this->points = 0;

}

TicTacToeScene::~TicTacToeScene()
{
	if (game != NULL)
	{
		delete game;
	}
}

bool TicTacToeScene::isOver(){
	return gameover;
}

bool TicTacToeScene::isWinner() {
	return winner;
}

float TicTacToeScene::getPoints(){
	return points;
}

//Initiate Scene
void TicTacToeScene::Init(void){

}

// Timer Callback
void TicTacToeScene::Timer(int value)
{
	//g_rotation += 0.01;
}

// Draw Callback
void TicTacToeScene::Draw(void)
{

}

void TicTacToeScene::Draw3dObjects(void)
{
	
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	// Define a viewing transformation
	gluLookAt(0.0, -1.5, 8, 1.5, -1.5, 0, 0, 1, 0);

	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others
	glPushMatrix(); //Save the transformations performed thus far

	//glRotatef(g_rotation, 0, 1, 0);

	// Draw board
	drawBoard();
	
	glPopMatrix();

}

void TicTacToeScene::DrawOverlay(void)
{
	// Draw the engine message
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);

	//position in the bottom-center:
	glRasterPos2f(0.6f, 0.5f);
	
	unsigned char msg[100];
	strcpy((char*) msg, game->getMessage().c_str());

	glutBitmapString(GLUT_BITMAP_HELVETICA_12, msg);
	//glEnable(GL_LIGHTING);

	glPopMatrix();
}

void TicTacToeScene::drawGrid(void)
{
	//Cilinder height
	float h = 3.0f;
	//Draw Grid
	glPushMatrix();

	//glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(90, 1, 0, 0);

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
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(w / -2.0f, w / 2.0f, 0.0f);
	glTranslatef(x, y, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glutSolidCylinder(0.1f, h, 10, 10);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(w, 0.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glutSolidCylinder(0.1f, h, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPopMatrix();

}

void TicTacToeScene::drawO(float x, float y)
{
	float r = 0.5f;
	int n = 20;

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(x, y, 0.0);
	glutSolidSphere(r, n, n);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void TicTacToeScene::drawBoard(){
	drawGrid();
	//Square1
	if (board[0] == COMPUTER)
		drawX(0.5f, -0.5f);
	else if (board[0] == HUMAN)
		drawO(0.5f, -0.5f);
	//Square2
	if (board[1] == COMPUTER)
		drawX(1.5f, -0.5f);
	else if (board[1] == HUMAN)
		drawO(1.5f, -0.5f);
	//Square3
	if (board[2] == COMPUTER)
		drawX(2.5f, -0.5f);
	else if (board[2] == HUMAN)
		drawO(2.5f, -0.5f);
	//Square4
	if (board[3] == COMPUTER)
		drawX(0.50f, -1.5f);
	else if (board[3] == HUMAN)
		drawO(0.50f, -1.5f);
	//Square5
	if (board[4] == COMPUTER)
		drawX(1.50f, -1.5f);
	else if (board[4] == HUMAN)
		drawO(1.50f, -1.5f);
	//Square6
	if (board[5] == COMPUTER)
		drawX(2.50f, -1.5f);
	else if (board[5] == HUMAN)
		drawO(2.50f, -1.5f);
	//Square7
	if (board[6] == COMPUTER)
		drawX(0.50f, -2.5f);
	else if (board[6] == HUMAN)
		drawO(0.50f, -2.5f);
	//Square8
	if (board[7] == COMPUTER)
		drawX(1.50f, -2.5f);
	else if (board[7] == HUMAN)
		drawO(1.50f, -2.5f);
	//Square9
	if (board[8] == COMPUTER)
		drawX(2.50f, -2.5f);
	else if (board[8] == HUMAN)
		drawO(2.50f, -2.5f);
	//glFlush();
}

// Keyboard callback
void TicTacToeScene::Key(unsigned char key, int x, int y) //The key that was pressed, and the current mouse coordenates
{
	SincroStatus();
	if (gameover) return;
	

		switch (key) {
		case '1':
			//if square 1 is empty
			if (board[0] == 0)
				board[0] = HUMAN;
			else return;
			break;
		case '2':
			//if square 2 is empty
			if (board[1] == 0)
				board[1] = HUMAN;
			else return;
			break;
		case '3':
			//if square 3 is empty
			if (board[2] == 0)
				board[2] = HUMAN;
			else return;
			break;
		case '4':
			//if square 4 is empty
			if (board[3] == 0)
				board[3] = HUMAN;
			else return;
			break;
		case '5':
			//if square 5 is empty
			if (board[4] == 0)
				board[4] = HUMAN;
			else return;
			break;
		case '6':
			//if square 6 is empty
			if (board[5] == 0)
				board[5] = HUMAN;
			else return;
			break;
		case '7':
			//if square 7 is empty
			if (board[6] == 0)
				board[6] = HUMAN;
			else return;
			break;
		case '8':
			//if square 8 is empty
			if (board[7] == 0)
				board[7] = HUMAN;
			else return;
			break;
		case '9':
			//if square 9 is empty
			if (board[8] == 0)
				board[8] = HUMAN;
			else return;
			break;
		case 27:
			//end game on ESC?
			break;
		}

		//pass digits to the game engine:
		if (isdigit(key))
		{
			// key to digit
			int square = key - 48;
			// Human Move
			game->playTTT(square);

			SincroStatus();

			if (gameover==false)
			// Computer Move
			board[game->getComputerMove() - 1] = COMPUTER;
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


//getStatus(2 - computer wins; 1 - human wins; 0 - draw; -1 - playing)
void TicTacToeScene::SincroStatus(){
	int i = game->getStatus();
	if (i < 0 ) gameover = false;
	else {
		if (i == 1) {
			winner = true;
			points = 200;
		}
		gameover = true;
	}
}