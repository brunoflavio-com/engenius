#include "HangmanScene.h"
#include <gl\freeglut.h>
#include <ctype.h>

HangmanScene::HangmanScene(SocialGamePublicAPIClient *client, string loginEmail){

	this->client = client;

	//retrieve info (categories/words)
	catVec = client->getCategories(5);
	categorySelectionMode = true;

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
	g_rotation += 0.01;
}

// Draw Callback
void HangmanScene::Draw(void)
{
	
}

void HangmanScene::Draw3dObjects(void){

	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Define a viewing transformation
	gluLookAt(0.0, -0.5, 6, 1.5, -1.5, 0, 0, 1, 0);
	
	
	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.
	glPushMatrix();
	
		glColor3f(1, 0, 0);
		glTranslatef(0, 0, 0);
		//glRotatef(g_rotation, 0, 1, 0);
		glRotatef(45, 0, 1, 0);
	
	glPopMatrix();

}

void HangmanScene::DrawOverlay(void) {

	if (categorySelectionMode) return showCategories(catVec);

	//Show space of letters
	drawOutputWord();
	drawMessage();
	
}

// Keyboard callback
void HangmanScene::Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		//end game on ESC?
		break;	
	}

	if (categorySelectionMode) {
		//catch integers
		if (key > '0' && key < '6') {

			selectedCategory = catVec.at((key - 48) - 1);
			word = client->getWord(catVec.at((key - 48)-1));

			game = new HangmanPLEngine(3, word.c_str());
			categorySelectionMode = false;
		}
	} else if (isalpha(key)) //pass letters to the game engine:
	{
		play(key);
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

//Draw the word in Output
void HangmanScene::drawOutputWord()
{
	glPushMatrix();
	// Draw the engine message
	glColor3f(1.0f, 1.0f, 1.0);
	//position in the center:
	glRasterPos2f(0.4, 0.4);

	unsigned char msg[100];
	
	strcpy((char*) msg, guessString().c_str());

	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, msg);

	glPopMatrix();

}

void HangmanScene::drawMessage(){
	// Draw the engine message
	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	//position in the center:
	glRasterPos2f(0.7f, 0.7f);

	unsigned char msg[100];
	strcpy((char*) msg, game->getMessage().c_str());

	glutBitmapString(GLUT_BITMAP_HELVETICA_12, msg);

	glPopMatrix();
}

string HangmanScene::guessString() 
{
	string output = "Category: " + selectedCategory + "\n\n";
	for (int i = 0; i < word.length(); i++)
	{
		char letter = word[i];
		//get chars
		if (std::find(letters.begin(), letters.end(), letter) != letters.end()) {
			output += letter;
		}
		else {
			output += '_';
		}
		output += ' ';
	}
	return output;
}

void HangmanScene::play(unsigned char key)
{
		letters.push_back(key);
		game->play(key);
	
}


void HangmanScene::showCategories(vector<string> categories){
	// Draw the engine message
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	//position in the center:
	glRasterPos2f(0.6f, 0.6f);
	
	string scr = "Select one category:\n";
	//scr = new string[categories.size()];
	for (int i = 0; i<categories.size(); i++){
		scr += to_string(i+1) + " " + categories[i] + "\n";//Copy the vector to the string
	}

	unsigned char msg[512];
	strcpy((char*) msg, scr.c_str());

	glutBitmapString(GLUT_BITMAP_HELVETICA_12, msg);

	glPopMatrix();
}


