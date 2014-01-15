#include "HangmanScene.h"
#include <gl\freeglut.h>
#include <ctype.h>

HangmanScene::HangmanScene(SocialGamePublicAPIClient *client, string loginEmail){
	//Soap Proxy to retrieve categories/words
	this->client = client;

	//retrieve 5 random categories
	catVec = client->getCategories(5);
	categorySelectionMode = true;

	points = 0;
	gameover = false;
	winner = false;
	
	gameoverDelay = 0;
}

HangmanScene::~HangmanScene()
{
	if (game != NULL)
	{
		delete game;
	}
	
}

//verify if gameover
bool HangmanScene::isOver(){
	return gameover;
}

//verify if there is a winner
bool HangmanScene::isWinner(){
	return winner;
}

//return points 
float HangmanScene::getPoints(){

	return points;
}

// Initiate scene
void HangmanScene::Init(void)
{

}

// Timer Callback
void HangmanScene::Timer(int value)
{
	currTime = time(0);

	if (currTime - startTime > gameoverDelay) {		
		gameover = true;
		startTime = 0;
		gameoverDelay = 0;
	}
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
	if(gameover) return;

		switch (key) {
		case 27:
			//end game on ESC?
			break;
		}

		//Select Categories
		if (categorySelectionMode) {
			//catch integers
			if (key > '0' && key < '6') {

				selectedCategory = catVec.at((key - 48) - 1);
				word = client->getWord(catVec.at((key - 48) - 1));

				game = new HangmanPLEngine(3, word.c_str());
				categorySelectionMode = false;
			}
		}
		//Find word mode
		else if (isalpha(key)) //pass letters to the game engine:
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
	glRasterPos2f(0.0, 0.5);

	unsigned char msg[100];
	
	strcpy((char*) msg, guessString().c_str());

	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, msg);

	glPopMatrix();

}

//Draw messages
void HangmanScene::drawMessage(){
	// Draw the engine message
	glPushMatrix();
	glColor3f(1.0f, 0, 0);
	//position in the center:
	glRasterPos2f(0.7f, -0.1f);

	unsigned char msg[100];
	strcpy((char*) msg, game->getMessage().c_str());

	glutBitmapString(GLUT_BITMAP_HELVETICA_12, msg);

	glPopMatrix();
}

//Show spaces and letters in word
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

//try letter, verify gameover, winner and points
void HangmanScene::play(unsigned char key)
{
		letters.push_back(key);
		game->play(key);
		if (game->isGameOver()) {
			gameoverDelay = 5;
			startTime = time(0);
		}
		//gameover=game->isGameOver();
		winner=game->isWinner();
		if (winner)
			points = PRIZE-(game->noOfRetries()*100);
	
}

//Prepare categories and prepare for selection
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

