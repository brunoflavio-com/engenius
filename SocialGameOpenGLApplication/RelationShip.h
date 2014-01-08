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
	int glId;
	float cylinderRadius;
	User * userA;
	User * userB;
	int strength;
	RelationshipTag * relationshipTag;

	Relationship();
	~Relationship();
	User * getDestinationUser(User * originUser);
	int getType();
};

