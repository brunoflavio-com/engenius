// SocialGameOpenGLApplication.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SocialGamePublicAPIClient.h"
#include <exception>
#include "GraphOpenGL.h"


int _tmain(int argc, char* argv[])
{
	string email;
	string password;
	/*
	std::cout << "Welcome to SocialGame\n";
	std::cout << "Username:";
	std::getline(std::cin, email);
	std::cout << "Username:";
	std::getline(std::cin, password);
	*/
	email = "test@test.com";
	password = "123456";
	
	SocialGamePublicAPIClient * client = new SocialGamePublicAPIClient();
	boolean login = client->Login(email, password);

	GraphOpenGL::Run(argc, argv, client, email);

	getchar();
	return 0;
}

