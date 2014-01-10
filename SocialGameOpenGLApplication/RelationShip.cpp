#include "Relationship.h"


Relationship::Relationship()
{
	walked = false;
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

bool Relationship::contains(User * user){
	if (userA == user || userB == user)
	{
		return true;
	}
	else { 
		return false; 
	}
}