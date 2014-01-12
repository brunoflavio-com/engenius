#pragma once
#include "IWindowScene.h"
#include "IMinigame.h"
#include "TicTacToePLEngine.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

#define HUMAN 1
#define COMPUTER 2 

class TicTacToeScene :
	public IWindowScene
{
public:

	TicTacToeScene(SocialGamePublicAPIClient *client, string loginEmail);
	~TicTacToeScene();

	//Implementation of IMinigame
	bool isOver();
	bool isWinner();
	float getPoints();

	// Initiate Scene
	void Init(void);

	//Timer Callback
	void Timer(int value);

	//Draw Callback
	void Draw(void);
	void Draw3dObjects(void);
	void DrawOverlay(void);

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

	//Board is a list with 9 elements
	int board[9];

	//Game Engine:
	TicTacToePLEngine * game;

	bool winner;
	bool gameover;
	float points;

	// Draw X in Board
	void drawX(float x, float y);
	// Draw O in Board
	void drawO(float x, float y);
	// Draw Board
	void drawBoard(void);
	// Draw Grid
	void drawGrid(void);
	//actualize winner,gameover,points
	void SincroStatus();
	//float g_rotation = 0.0;

};

