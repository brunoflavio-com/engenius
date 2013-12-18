#pragma once
#include "User.h"
#include "RelationshipTag.h"

using namespace std;
class User;
class Relationship
{
	public:
	User * user;
	int strength;
	RelationshipTag * relationshipTag;

	Relationship();
	~Relationship();
};

