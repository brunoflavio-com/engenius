#pragma once
#include "IWindowScene.h"
#include "HangmanPLEngine.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

class HangmanScene :
	public IWindowScene
{
public:
	HangmanScene(SocialGamePublicAPIClient *client, string loginEmail);
	~HangmanScene();

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
	//Soap Proxy to retrieve categories/words?
	
	//teapot example:
	float g_rotation = 0.0;
};

