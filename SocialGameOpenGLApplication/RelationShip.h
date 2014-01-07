#pragma once
#include "ISelectable.h"
#include "User.h"
#include "RelationshipTag.h"

using namespace std;
class User;
class Relationship :
	public ISelectable
{
	public:
	User * user;
	int strength;
	RelationshipTag * relationshipTag;

	Relationship();
	~Relationship();
};

