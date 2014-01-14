#pragma once
#include "GraphScene.h"
#include "GraphPLEngine.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

class AdvanceModeGraphScene :
	public GraphScene
{
private:
	GraphPLEngine pl;

	ISelectable * previousSelectable;

	vector<Relationship *> shortestPath;
	vector<Relationship *> strongestPath;

	void highlight(bool value);

public:
	AdvanceModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail);
	void DrawOverlay(void);
	void Draw3dObjects(void);
	~AdvanceModeGraphScene();
	Graph * getGraph(std::string loginEmail, int level);
	void verticeClicked(User * previousUser, User * nextUser);
	void Timer(int value);
	
	void PassiveMotion(int newx, int newy);

	bool showShortestPath;
	bool showStrongestPath;
};

