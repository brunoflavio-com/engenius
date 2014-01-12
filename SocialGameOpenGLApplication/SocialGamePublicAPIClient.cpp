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


std::future<bool> SocialGamePublicAPIClient::asyncLogin(std::string email, std::string password){
	if (ready){
		return std::async(&SocialGamePublicAPIClient::Login, this, email, password);
	}
	else{
		throw std::exception();
	}
}

bool SocialGamePublicAPIClient::Login(std::string email, std::string password){
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

std::future<ns5__Graph * > SocialGamePublicAPIClient::asyncGetGraph(std::string email, int depth){
	if (ready){
		return std::async(&SocialGamePublicAPIClient::getGraph, this, email, depth);
	}
}

ns5__Graph * SocialGamePublicAPIClient::getGraph(std::string email, int depth){
	if (ready && LoggedIn){
		ready = false;
		_ns1__GetGraph getGraph;
		getGraph.graphDepth = &depth;
		getGraph.Token = &token;
		getGraph.Email = &email;
		_ns1__GetGraphResponse response;
		proxy.GetGraph(&getGraph, &response);
		ns5__Graph * graph = response.GetGraphResult;
		ready = true;
		return graph;
	}
	else{

		throw std::exception();
	}
	return NULL;
}

void SocialGamePublicAPIClient::getUserGameInfo(int & level, float &points){
	if (ready && LoggedIn){
		ready = false;
		_ns1__getUserGameInfo userGameInfo;
		userGameInfo.Token = &token;
		_ns1__getUserGameInfoResponse response;
		proxy.getUserGameInfo(&userGameInfo, &response);

		ns5__UserGameInfo * result = response.getUserGameInfoResult;

		level = * result->Level;
		points = *result->Points;
		ready = true;
	}
	else{
		throw std::exception();
	}
	return;
}

std::vector<std::string> SocialGamePublicAPIClient::getCategories(int numberOfCategories){

	if (ready && LoggedIn){
		ready = false;
		_ns1__getRandomWordCategories getRandomWordCategories;
		getRandomWordCategories.Token = &token;
		getRandomWordCategories.number = &numberOfCategories;
		_ns1__getRandomWordCategoriesResponse response;
		proxy.getRandomWordCategories(&getRandomWordCategories, &response);
		arr__ArrayOfstring * vCategories = response.getRandomWordCategoriesResult;

		vector<string> categories;
		for (int i = 0; i < numberOfCategories; i++){
			categories.push_back(vCategories->string.at(i).c_str());			
		}

		ready = true;
		return categories;
	}
	else{

		throw std::exception();
	}
}

std::string SocialGamePublicAPIClient::getWord(string category){

	if (ready && LoggedIn){
		ready = false;
		_ns1__getRandomWordFromCategory getRandomWordFromCategory;
		getRandomWordFromCategory.Token = &token;
		getRandomWordFromCategory.category = &category;
		_ns1__getRandomWordFromCategoryResponse response;
		proxy.getRandomWordFromCategory(&getRandomWordFromCategory, &response);
		string * word = response.getRandomWordFromCategoryResult;
		ready = true;
		return *word;
	}
	else{

		throw std::exception();
	}
}

std::string SocialGamePublicAPIClient::getMazeMap(int level){

	if (ready && LoggedIn){
		ready = false;
		_ns1__getMaze getMaze;
		getMaze.Token = &token;
		getMaze.id = &level;
		_ns1__getMazeResponse response;
		proxy.getMaze(&getMaze, &response);
		string * map = response.getMazeResult;
		ready = true;
		return *map;
	}
	else{

		throw std::exception();
	}
}

