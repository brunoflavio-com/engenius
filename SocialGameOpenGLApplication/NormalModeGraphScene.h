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

public:
	NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail);
	~NormalModeGraphScene();
	
	void DrawOverlay(void);
	void Draw3dObjects(void);
	
	void Key(unsigned char key, int x, int y);
	void Timer(int value);
};
