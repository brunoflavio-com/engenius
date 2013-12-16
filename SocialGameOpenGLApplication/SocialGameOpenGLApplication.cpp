// SocialGameOpenGLApplication.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SocialGamePublicAPIClient.h"
#include <exception>

int _tmain(int argc, _TCHAR* argv[])
{
	SocialGamePublicAPIClient * client = new SocialGamePublicAPIClient();
	std::future<boolean> login1 = client->asyncLogin("xiko","qwerty");

	getchar();
	return 0;
}

