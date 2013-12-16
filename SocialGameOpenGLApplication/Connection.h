#pragma once
#include "User.h"
#include "ConnectionTag.h"

class Connection
{
public:
	User user;
	int strength;
	ConnectionTag connectionTag;
	Connection();
	~Connection();
};

