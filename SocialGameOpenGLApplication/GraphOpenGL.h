#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include "SocialGamePublicAPIClient.h"
#include "GraphScene.h"

class GraphScene;

class GraphOpenGL
{
private:
	static GraphScene * currentScene;
	static GraphScene * advanceScene;
	static GraphScene  * normalScene;
	static bool advancedMode;
public:
	
	GraphOpenGL();
	~GraphOpenGL();
	void static myortho(void);
	void static Init();
	void static subWindowInit();
	void static	passiveMotion(int newx, int newy);
	void static MotionMouse(int x, int y);
	void static Mouse(int button, int state, int x, int y);
	void static ReshapeMinimap(int width, int height);
	void static Reshape(int width, int height);
	void static DrawMinimap();
	void static Draw();
	void static redisplayAll(void);
	void static Timer(int value);
	void static PrintKeys();
	void static Key(unsigned char key, int x, int y);
	void static SpecialKey(int key, int x, int y);
	void static SpecialKeyUp(int key, int x, int y);
	void static Run(int argc, char **argv, SocialGamePublicAPIClient * client, std::string login);
};
