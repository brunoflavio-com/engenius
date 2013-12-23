#include "HangmanScene.h"
#include <gl\freeglut.h>
#include <ctype.h>


HangmanScene::HangmanScene()
{
	//retrieve info (categories/words)

	//initialize game engine:
	game = new HangmanPLEngine(3, "engenius");

}

HangmanScene::~HangmanScene()
{
	if (game != NULL)
	{
		delete game;
	}
	
}

// Initiate scene
void HangmanScene::Init(void)
{

}

// Timer Callback
void HangmanScene::Timer(int value)
{
	g_rotation += 0.1;
}

// Draw Callback
void HangmanScene::Draw(void)
{
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Define a viewing transformation
	gluLookAt(4, 2, 0, 0, 0, 0, 0, 1, 0);


	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 0, 0);
	glRotatef(g_rotation, 0, 1, 0);
	glRotatef(90, 0, 1, 0);

	// Draw the teapot
	glutSolidTeapot(1);
	glPopMatrix();

	//Draw the game engine message:
	glPushMatrix();
		unsigned char msg[100];
		strcpy((char*)msg, game->getMessage().c_str());

		glutBitmapString(GLUT_BITMAP_HELVETICA_12, msg);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

// Keyboard callback
void HangmanScene::Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		//end game on ESC?
		break;	
	}

	//pass letters to the game engine:
	if (isalpha(key))
	{
		game->play(key);
	}
}

// Special key callback
void HangmanScene::SpecialKey(int key, int x, int y)
{

}

// Special key UP callback
void HangmanScene::SpecialKeyUp(int key, int x, int y)
{

}

// Mouse Callbacks
void HangmanScene::Mouse(int btn, int state, int x, int y)
{

}

void HangmanScene::MotionMouse(int x, int y)
{

}