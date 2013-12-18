// SocialGameOpenGLApplication.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SocialGamePublicAPIClient.h"
#include "User.h"
#include <exception>

int _tmain(int argc, _TCHAR* argv[])
{
	SocialGamePublicAPIClient * client = new SocialGamePublicAPIClient();
	std::cout << "Start";
	boolean login = client->Login("test@test.com","123456");
	std::cout << "Loggin";
	

	if (login)
	{
		std::cout << "True";
	}
	else
	{
		std::cout << "Not True";
	}
	User * user = client->getGraph("test@test.com", 2);



	getchar();
	return 0;
}

