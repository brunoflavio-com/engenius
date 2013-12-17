#include "SocialGamePublicAPIClient.h"
#include "gsoapAPIClient\BasicHttpBinding_USCOREISocialGameService.nsmap"


SocialGamePublicAPIClient::SocialGamePublicAPIClient()
{
	this->ready = true;
	this->LoggedIn = false;
}


SocialGamePublicAPIClient::~SocialGamePublicAPIClient()
{
}


std::future<boolean> SocialGamePublicAPIClient::asyncLogin(std::string email, std::string password){
	if (ready){
		return std::async(&SocialGamePublicAPIClient::Login, this, email, password);
	}
	else{
		throw std::exception();
	}
}

boolean SocialGamePublicAPIClient::Login(std::string email, std::string password){
	ready = false;
	_ns1__Login login;

	login.Email = &email;
	login.Password = &password;

	_ns1__LoginResponse loginResponse;

	if (proxy.Login(&login, &loginResponse) == SOAP_OK){
		std::string * Token = loginResponse.LoginResult;
		this->token = *Token;
		LoggedIn = true;
		ready = true;
		return true;
	}
	else{
		ready = true;
		return false;
	}
}

std::future<boolean> SocialGamePublicAPIClient::asyncGetGraph(std::string email, int depth){
	if (ready){
		return std::async(&SocialGamePublicAPIClient::getGraph, this, email, depth);
	}
}

boolean SocialGamePublicAPIClient::getGraph(std::string email, int depth){
	if (ready && LoggedIn){
		ready = false;
		_ns1__GetGraph getGraph;
		getGraph.graphDepth = &depth;
		getGraph.Token = &token;
		getGraph.Email = &email;
		_ns1__GetGraphResponse response;
		proxy.GetGraph(&getGraph, &response);
		ns3__UserContract * user = response.GetGraphResult;
		ready = true;
	}
	else{

		throw std::exception();
	}
}

