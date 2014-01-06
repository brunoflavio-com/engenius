#pragma once
#include "IBothWindowScene.h"
#include "SocialGamePublicAPIClient.h"
#include "graphCoordWalker.h"
#include "GraphWalkerDraw.h"
#include "GraphOpenGL.h"
#include <string>
#include "User.h"
#include <GL/glut.h>
#include "Graph.h"

class GraphScene :
	public IBothWindowsScene
{
private:
	void static myortho(void);

protected: 
	bool isSubWindowsActive;
	SocialGamePublicAPIClient * apiClient;
	string email;
	Graph * graph;
	bool onGame;

public:
	GraphScene(SocialGamePublicAPIClient *, string loginEmail);
	~GraphScene();
	

	void Init(void);
	void subWindowInit(void);
	void Timer(int value);

	// Callback de desenho
	void Draw(void);

	// Callback para interacção via teclado (carregar na tecla)
	void Key(unsigned char key, int x, int y);

	// Callback para interacção via teclas especiais  (carregar na tecla)
	void SpecialKey(int key, int x, int y);

	// Callback para interacção via teclas especiais (largar a tecla)
	void SpecialKeyUp(int key, int x, int y);

	void drawSubWindow();
	bool isSubWindowActive();
	void StartCam();

	void CamLookAt();

	void TopCamLookAt();
	void MotionMouse(int x, int y);
	void PassiveMotion(int newx, int newy);
	void Mouse(int button, int state, int x, int y);
};

