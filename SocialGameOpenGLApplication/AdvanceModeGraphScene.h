#pragma once
#include "GraphScene.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

class AdvanceModeGraphScene :
	public GraphScene
{
public:
	AdvanceModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail);
	void DrawOverlay(void);
	void Draw3dObjects(void);
	~AdvanceModeGraphScene();
	Graph * getGraph(std::string loginEmail, int level);
	void verticeClicked(User * previousUser, User * nextUser);
	void Timer(int value);

};

