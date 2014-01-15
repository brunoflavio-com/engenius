#pragma once
#include "IWindowScene.h"
#include "IMinigame.h"
#include "MazeMap.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

namespace MinigamesMaze{
	class MazeScene : 
		public IWindowScene, public IMinigame
	{
	public:
		MazeScene(SocialGamePublicAPIClient* client, string loginEmail, int level);
		~MazeScene();

		// Initiate Scene
		void Init(void);

		//Timer Callback
		void Timer(int value);

		//Implementation of IMinigame
		bool isOver();
		bool isWinner();
		float getPoints();


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
		//Maximum number of points
		const float MAX_POINTS = 5000.0f;

		SocialGamePublicAPIClient* client;

		//keys
		struct{
			bool up;
			bool down;
			bool left;
			bool right;
		} arrowKeys;

		// Map
		MazeMap* map;

		//Current Points
		float points;
		int timePoints;

		bool giveUp;

		//Over and Win flags
		bool over;
		bool winner;

		//Position
		float xPosition;
		float yPosition;
		float zPosition;

		bool hintPressed;
		int maxHintSeconds = 2;
		long currTime;
		long hintStart;
		int level;

		float cubeAndSphereSize = 1.0f;

		void drawMap(void);
		void drawCube(float x, float y, float z, float side);
		void drawSphere(float x, float y, float z, float radius);
		void drawSquare(float x, float y, float z, float side);
		void drawHint();
		bool colision();

		void calculatePoints();
	};
}
