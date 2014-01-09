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
	ISelectable * pickISelectable( int x, int y);

protected: 
	bool isSubWindowsActive;
	Graph * graph;

public:
	string email;
	SocialGamePublicAPIClient * apiClient;

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
	void CamMovement();
	void TopCamLookAt();

	void MotionMouse(int x, int y);
	void PassiveMotion(int newx, int newy);
	void Mouse(int button, int state, int x, int y);

	bool ColisionTest(int newx, int newy);

	virtual Graph * getGraph(std::string loginEmail, int level) = 0;
	virtual void moveGraphToNewUser(User * user) = 0;
};

