#pragma once
#include "SceneInterface.h"
#include "SocialGamePublicAPIClient.h"
#include <string>
#include "User.h"
#include <GL/glut.h>

class GraphScene :
	public InterfaceScene
{
protected: 
	SocialGamePublicAPIClient * apiClient;
	string email;
	User * graph;
public:
	void Draw(void);
	void Key(unsigned char key, int x, int y);
	void KeyUp(unsigned char key, int x, int y);
	GraphScene(SocialGamePublicAPIClient *, string loginEmail);
	~GraphScene();
};

