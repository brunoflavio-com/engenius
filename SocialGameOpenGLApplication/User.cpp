#include "User.h"


User::User()
{
	graphLevel = -1;
	userTags = new vector<UserTag * >();
	relationships = new vector<Relationship *>();
}


User::~User()
{
}
