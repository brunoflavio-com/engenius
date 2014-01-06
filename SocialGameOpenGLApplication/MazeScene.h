#pragma once
#include "IWindowScene.h"
#include "MazePlEngine.h"
#include "MazeMap.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

namespace MinigamesMaze{
	class MazeScene : 
		public IWindowScene
	{
	public:
		MazeScene();
		MazeScene(SocialGamePublicAPIClient *client, string loginEmail);
		~MazeScene();

		// Initiate Scene
		void Init(void);

		//Timer Callback
		void Timer(int value);

		//Draw Callback
		void Draw(void);
		void Draw3dObjects(void);
		void DrawOverlay(void);

		//Keyboard Callback
		void Key(unsigned char key, int x, int y);

		//Special Key Callback
		void SpecialKey(int key, int x, int y);

		//Special Key UP Callback
		void SpecialKeyUp(int key, int x, int y);

		//Mouse Callbacks
		void Mouse(int btn, int state, int x, int y);
		void MotionMouse(int x, int y);

	private:
		// Map
		MazeMap* map;

		//Game Engine
		MazePlEngine* game;

		float g_rotation = 0.0;

		void drawMap(void);
		void drawCube(float x, float y, float z, float side);
	};
}