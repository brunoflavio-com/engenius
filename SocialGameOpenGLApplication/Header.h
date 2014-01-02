#pragma once
#include "ISubWindowScene.h"
#include "IWindowScene.h"

class IBothWindowsScene : 
	public ISubWindowScene, public IWindowScene
{

};
