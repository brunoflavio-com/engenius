#pragma once
class ISubWindowScene
{
public:
	virtual void subWindowInit(void) = 0;
	virtual void drawSubWindow() = 0;
	virtual bool isSubWindowActive() = 0;
};

