#pragma once
#include "IWindowScene.h"
#include "IMinigame.h"
#include "HangmanPLEngine.h"
#include "SocialGamePublicAPIClient.h"
#include <string>



class HangmanScene :
	public IWindowScene, public IMinigame
{
public:
	HangmanScene(SocialGamePublicAPIClient *client, string loginEmail);
	~HangmanScene();

	//Implementation of IMinigame
	bool isOver();
	bool isWinner();
	float getPoints();

	// Initiate scene
	void Init(void);

	// Timer Callback
	void Timer(int value);

	// Draw Callback
	void Draw(void);
	void DrawOverlay(void);
	void Draw3dObjects(void);

	// Keyboard callback
	void Key(unsigned char key, int x, int y);

	// Special key callback
	void SpecialKey(int key, int x, int y);

	// Special key UP callback
	void SpecialKeyUp(int key, int x, int y);

	// Mouse Callbacks
	void Mouse(int btn, int state, int x, int y);
	void MotionMouse(int x, int y);

private:
	//Game engine:
	HangmanPLEngine * game;

	//Soap Proxy to retrieve categories/words
	SocialGamePublicAPIClient *client;

	//Category selection mode
	bool categorySelectionMode;

	//Vector with categories
	vector<string> catVec;

	//Vector with letters
	vector<char> letters;

	//Selected Category
	string selectedCategory;

	//Word to find
	string word;
	
	//rotation
	//float g_rotation = 0.0;

	//Draw OutPuts
	void drawOutputWord();
	void drawMessage();

	//Output word in progress
	string guessString();

	//Send letter to prolog
	void play(unsigned char key);

	//Send radom categories to output
	void showCategories(vector<string> categories);

	// Game is Over?
	bool gameover;

	// Player win?
	bool winner;

	// Player Points
	float points;
};

