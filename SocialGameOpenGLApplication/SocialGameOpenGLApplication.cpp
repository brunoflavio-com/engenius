// SocialGameOpenGLApplication.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SocialGamePublicAPIClient.h"
#include "User.h"
#include <exception>
#include "GraphOpenGL.h"

int _tmain(int argc, char* argv[])
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
	InterfaceGL * jogo = new GraphOpenGL();// apartir daqui

	jogo->Run(argc,argv);

	getchar();
	return 0;
}

