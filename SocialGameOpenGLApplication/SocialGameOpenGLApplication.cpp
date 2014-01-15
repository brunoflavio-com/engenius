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
	bool login = false;
	SocialGamePublicAPIClient * client = new SocialGamePublicAPIClient();

	while (!login) {
		std::cout << endl << endl << "Welcome to SocialGame";
		std::cout << endl << "Username:";
		std::getline(std::cin, email);
		std::cout << "Password:";

		//hide user input:
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode = 0;
		GetConsoleMode(hStdin, &mode);
		SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

		//read password
		std::getline(std::cin, password);

		//restore user input:
		SetConsoleMode(hStdin, mode);
		
		login = client->Login(email, password);
	}

	GraphOpenGL::Run(argc, argv, client, email);

	getchar();
	return 0;
}

