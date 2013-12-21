#pragma once
#include "SceneInterface.h"
#include "SubWindowSceneInterface.h"
#include "SocialGamePublicAPIClient.h"
#include "graphCoordWalker.h"
#include "GraphWalkerDraw.h"
#include "GraphOpenGL.h"
#include <string>
#include "User.h"
#include <GL/glut.h>

class GraphScene :
	public InterfaceScene, public SubWindowSceneInterface
{
private:
	int maxUserConnections;
	int maxConnectionStrenght;

protected: 
	bool isSubWindowsActive;
	SocialGamePublicAPIClient * apiClient;
	string email;
	User * graph;
	InterfaceScene * gameScene;
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

	void Mouse(int button, int state, int x, int y);
};

