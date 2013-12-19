#pragma once
#include <string>
#include <iostream>
#include <future>
#include "User.h" 
#include "gsoapAPIClient\soapBasicHttpBinding_USCOREISocialGameServiceProxy.h"

class SocialGamePublicAPIClient
{
private:
	BasicHttpBinding_USCOREISocialGameServiceProxy proxy;
	std::string token;
public:
	std::atomic<bool> ready;
	std::atomic<bool> LoggedIn;
	SocialGamePublicAPIClient();
	bool Login(std::string userName, std::string Password);
	std::future<bool> asyncLogin(std::string userName, std::string Password);
	User * getGraph(std::string email, int depth);
	std::future<User * > asyncGetGraph(std::string email, int depth);
	~SocialGamePublicAPIClient();
};

