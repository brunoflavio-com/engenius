#include "SocialGamePublicAPIClient.h"
#include "gsoapAPIClient\BasicHttpBinding_USCOREISocialGameService.nsmap"
#include "SocialGamePublicAPIConverter.h"

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

		if (!Token->empty()){
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
	else{
		ready = true;
		return false;
	}
}

std::future<User * > SocialGamePublicAPIClient::asyncGetGraph(std::string email, int depth){
	if (ready){
		return std::async(&SocialGamePublicAPIClient::getGraph, this, email, depth);
	}
}

User * SocialGamePublicAPIClient::getGraph(std::string email, int depth){
	if (ready && LoggedIn){
		ready = false;
		_ns1__GetGraph getGraph;
		getGraph.graphDepth = &depth;
		getGraph.Token = &token;
		getGraph.Email = &email;
		_ns1__GetGraphResponse response;
		proxy.GetGraph(&getGraph, &response);
		ns5__Graph * graph = response.GetGraphResult;
		SocialGamePublicAPIConverter * converter = new SocialGamePublicAPIConverter();
		User * user = converter->convertGraph(graph, email);
		ready = true;
		return user;
	}
	else{

		throw std::exception();
	}
}

