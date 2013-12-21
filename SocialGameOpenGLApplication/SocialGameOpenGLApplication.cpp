// SocialGameOpenGLApplication.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SocialGamePublicAPIClient.h"
#include "User.h"
#include <exception>
#include "GraphOpenGL.h"
#include "graphCoordWalker.h"
#include "GraphScene.h"
#include "SceneInterface.h"
#include "SubWindowSceneInterface.h"

int _tmain(int argc, char* argv[])
{
	

	SocialGamePublicAPIClient * client = new SocialGamePublicAPIClient();
	std::cout << "Start";
	string email = "test@test.com";
	string password = "123456";
	boolean login = client->Login(email, password);
	std::cout << "Loggin";


	if (login)
	{
		std::cout << "True";
	}
	else
	{
		std::cout << "Not True";
	}
	
	GraphScene * scene = new GraphScene(client, email);
	std::cout << "Scene created";

	GraphOpenGL::Run(argc, argv, (InterfaceScene *)scene, (SubWindowSceneInterface *)scene);

	getchar();
	return 0;
}

