#pragma once
#include "IBothWindowScene.h"
#include "SocialGamePublicAPIClient.h"
#include "GraphPositionWalker.h"
#include "GraphWalkerDraw.h"
#include "GraphOpenGL.h"
#include <string>
#include "User.h"
#include <GL/glut.h>
#include "Graph.h"
#include "ISelectable.h"

class GraphScene :
	public IBothWindowsScene
{
private:


	ISelectable * pickISelectable( int x, int y);
	
	string message;
	int messageUpdateTime;
	bool isMessageActive;
	
protected: 
	bool isSubWindowsActive;
	Graph * graph;
	ISelectable * selectedObject = NULL;
	atomic<int> glTime;
public:
	bool isFinished;
	bool returningToGame;
	string returningMessage;
	User * realUser;
	int userLevel;
	float userPoints;
	string email;
	string name;
	SocialGamePublicAPIClient * apiClient;

	GraphScene(SocialGamePublicAPIClient *, string loginEmail);
	~GraphScene();
	

	void Init(void);
	void subWindowInit(void);
	void Timer(int value);

	// Callback de desenho
	void Draw(void);
	void DrawSkybox(GLdouble x, GLdouble y, GLdouble z);

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

	bool ColisionTest(GLdouble newx, GLdouble newy, GLdouble newz);
	void drawPositionIndications(int numberOfIndications,GLfloat colors[][4], const unsigned char textIndications[][20]);
	virtual Graph * getGraph(std::string loginEmail, int level) = 0;
	virtual void verticeClicked(User * previousUser, User * nextUser) = 0;
	void getUserPointsAndLevel();
	void createMessage(std::string message);

};

