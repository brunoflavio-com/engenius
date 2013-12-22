#pragma once
#include "SceneInterface.h"
class HangmanScene :
	public InterfaceScene
{
public:
	HangmanScene();
	~HangmanScene();

	// Initiate scene
	void Init(void);

	// Timer Callback
	void Timer(int value);

	// Draw Callback
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
	//Prolog engine:
	//Soap Proxy to retrieve categories/words?
	
	//teapot example:
	float g_rotation = 0.0;
};

