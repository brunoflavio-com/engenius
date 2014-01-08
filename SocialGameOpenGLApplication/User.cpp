#include "User.h"


User::User()
{
	graphLevel = -1;
}


User::~User()
{
}

int User::getType(){
	return USER_TYPE;
}