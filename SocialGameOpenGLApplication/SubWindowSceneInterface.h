#pragma once
class SubWindowSceneInterface
{
public:
	SubWindowSceneInterface();
	~SubWindowSceneInterface();

	virtual void subWindowInit(void) = 0;
	virtual void drawSubWindow() = 0;
	virtual bool isSubWindowActive() = 0;
};

