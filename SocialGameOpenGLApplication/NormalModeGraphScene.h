#pragma once
#include "GraphScene.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

class NormalModeGraphScene :
	public GraphScene
{
private:
	bool gameOn;
	IWindowScene * game;
	User * targetUser;

public:

	NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail, int level);
	~NormalModeGraphScene();

	void DrawOverlay(void);
	void Draw3dObjects(void);

	void Key(unsigned char key, int x, int y);
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void Timer(int value);

	void PassiveMotion(int x, int y);
	void verticeClicked(User * previousUser, User * nextUser);

	Graph * getGraph(std::string loginEmail ,int level);

};

