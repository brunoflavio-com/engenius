#include "User.h"


User::User()
{
	userTags = new vector<UserTag * >();
	relationships = new vector<Relationship *>();
}


User::~User()
{
}
