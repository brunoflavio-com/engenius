#pragma once
#include "SceneInterface.h"
#include "TicTacToePLEngine.h"


class TicTacToeScene :
	public InterfaceScene
{
public:

	char board[9];

	TicTacToeScene();
	~TicTacToeScene();

	// Initiate Scene
	void Init(void);

	//Timer Callback
	void Timer(int value);

	//Draw Callback
	void Draw(void);

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
	//Game Engine:
	TicTacToePLEngine * game;


	// Draw X in Board
	void drawX(float x, float y);
	// Draw O in Board
	void drawO(float x, float y);
	// Draw Board
	void drawBoard(void);
	//Draw Grid
	void drawGrid(void);

};

