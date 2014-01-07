#include "Relationship.h"


Relationship::Relationship()
{
}


Relationship::~Relationship()
{
}

User * Relationship::getDestinationUser(User * originUser){

	if (originUser == userA)
	{
		return userB;
	}
	else{
		return userA;
	}
}

int Relationship::getType(){
	return RELATIONSHIP_TYPE;
}