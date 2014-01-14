#include "Graph.h"
#include "GraphPositionWalker.h"
#include "GraphWalkerDraw.h"

Graph::Graph()
{
}

void Graph::draw(bool drawUserName){
	GraphWalkerDraw drawWalker(drawUserName);
	drawWalker.walk(user,3);
}

void Graph::movetoVertice(User * nextUser){
	for each(User * tempUser in users){
		tempUser->graphLevel = -1;
		tempUser->cota = 0;
		tempUser->isCenter = false;
	}
	Relationship * relationship = getRelationship(user,nextUser);
	relationship->walked = true;

	user = nextUser;
	GraphPositionWalker coordWalker(maxUserConnections,maxConnectionStrenght,maxUserTags);
	coordWalker.walk(user);
	user->isCenter = true;
}


Graph::~Graph()
{
	for each (User * var in users)
	{
		delete var;
	}

	for each (HumorStatus * var in humorStatus)
	{
		delete var;
	}

	for each (RelationshipTag * var in relationShipTags)
	{
		delete var;
	}

	for each (Relationship * var in relationShips)
	{
		delete var;
	}

	for each (UserTag * var in userTags)
	{
		delete var;
	}
}

HumorStatus *  Graph::getHumorStatus(int id){
	for (unsigned int i = 0; i < humorStatus.size(); i++){
		if (humorStatus.at(i)->id == id)
		{
			return humorStatus.at(i);
		}
	}
}

UserTag *  Graph::getUserTag(int id){
	for (unsigned int i = 0; i < userTags.size(); i++){
		if (userTags.at(i)->id == id)
		{
			return userTags.at(i);
		}
	}
}

User *  Graph::getUser(string email){
	for (unsigned int i = 0; i < users.size(); i++){

		if (email.compare(users.at(i)->email) == 0)
		{
			return users.at(i);
		}
	}


}

RelationshipTag *  Graph::getRelationshipTag(int id){
	for (unsigned int i = 0; i < relationShipTags.size(); i++){

		if (relationShipTags.at(i)->id == id)
		{
			return relationShipTags.at(i);
		}
	}
}

Relationship * Graph::getRelationship(User * userA, User * userB){
	for each(Relationship * r in relationShips){
		if (r->contains(userA) && r->contains(userB)){
			return r;
		}
	}
	return NULL;
}