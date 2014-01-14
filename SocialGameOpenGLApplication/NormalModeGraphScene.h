#pragma once
#include "GraphScene.h"
#include "SocialGamePublicAPIClient.h"
#include <string>
#include <vector>
#include "GraphPLEngine.h"

class NormalModeGraphScene :
	public GraphScene
{
private:
	GraphPLEngine pl;

	bool gameOn;
	IWindowScene * game;
	User * targetUser;

	bool showShortestPath;
	vector<Relationship *> shortestPath;
	void toggleStrongestPath();

	bool showStrongestPath;
	vector<Relationship *> strongestPath;
	void toggleShortestPath();

	User * previousUser;
	User * nextUser;

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
	void advanceToNextVertice();

	Graph * getGraph(std::string loginEmail ,int level);

};

