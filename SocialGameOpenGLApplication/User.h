#pragma once
#include "Connection.h";
#include "UserTag.h"
#include "Humor.h";
#include <vector>

using namespace std;
class User
{
public:
	string email;
	string name;
	string surname;
	float cota;
	float x, y, z;

	 vector<Connection> connections;
	 vector<UserTag> userTags;
	 
	 Humor humor;
	User();
	~User();
};

