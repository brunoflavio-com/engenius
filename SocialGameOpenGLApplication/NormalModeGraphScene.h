#pragma once
#include "GraphScene.h"
#include "SocialGamePublicAPIClient.h"
#include <string>

class NormalModeGraphScene :
	public GraphScene
{
private:
	bool gameOn;

public:
	NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail);
	~NormalModeGraphScene();
	void DrawOverlay(void);
	void Draw3dObjects(void);
};

