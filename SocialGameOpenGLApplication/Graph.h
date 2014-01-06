#pragma once
#include "User.h"
#include "SocialGamePublicAPIConverter.h"
#include "gsoapAPIClient\soapBasicHttpBinding_USCOREISocialGameServiceProxy.h"
#include <string>
class Graph
{
private:
	User * user;
	SocialGamePublicAPIConverter converter;
	int maxUserConnections;
	int maxConnectionStrenght;
public:
	Graph(ns5__Graph * graph, std::string);
	~Graph();
	void draw(bool drawUserName);
	void changeUser(std::string email);
};

