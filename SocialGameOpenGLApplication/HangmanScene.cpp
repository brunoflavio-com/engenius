#include "HangmanScene.h"
#include <gl/glut.h>


HangmanScene::HangmanScene()
{
	//retrieve info (categories/words)

	//initialize prolog
	
}

HangmanScene::~HangmanScene()
{

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

	glutSwapBuffers();
}

// Keyboard callback
void HangmanScene::Key(unsigned char key, int x, int y)
{

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