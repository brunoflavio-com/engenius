// serviceClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include "client\soapBasicHttpBinding_USCOREIService1Proxy.h"
#include "client\BasicHttpBinding_USCOREIService1.nsmap"

int _tmain(int argc, _TCHAR* argv[])
{
	//Proxy class for service

	 BasicHttpBinding_USCOREIService1Proxy proxy;
	
	 // Login
	 
	std::string email = "xiko";
	std::string password = "qwerty";
	_ns1__Login login;
	
	login.Email = &email;
	login.Password = &password;
	
	_ns1__LoginResponse loginResponse;
	
	proxy.Login(&login, &loginResponse);

	std::string * Token = loginResponse.LoginResult;
	proxy.soap_stream_fault(std::cout);
	std::cout << *Token << std::endl;
	
	getchar();
	
	
	//GetGraph
	_ns1__GetGraph getGraph;

	int depth = 3;

	getGraph.graphDepth = &depth;
	getGraph.Token = Token;
	getGraph.Email = &email;
	
	_ns1__GetGraphResponse response;

	proxy.GetGraph(&getGraph, &response);
	proxy.soap_stream_fault(std::cout);
	
	ns3__User * user = response.GetGraphResult;
	std::cout << *user->Username << std::endl;
	
	std::cout << "Ligacoes"<<std::endl;

	for (int i = 0; i < user->Connections->Connection.size(); i++){
		ns3__Connection * conn= user->Connections->Connection.at(i);
		std::cout << *conn->User->Username<< " ";
		std::cout << *conn->ConnectionTag->ConnectionTagName << std::endl;
	}


	std::cout << "UserTags" << std::endl;
	
	for (int i = 0; i < user->UserTags->UserTag.size(); i++){
		ns3__UserTag * uTag = user->UserTags->UserTag.at(i);
		std::cout << *uTag->UserTagName << std::endl;

	}
	getchar(); 
	return 0;
}
