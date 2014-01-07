#include "GraphFactory.h"
#include <string>
#include "RelationShip.h"
#include "RelationShipTag.h"
#include <vector>
#include "graphCoordWalker.h"
#include <stdio.h>
#include <stdlib.h>


Graph * GraphFactory::buildRandomGraph(int graphDepth, std::string email){
	Graph * graph = new Graph();

	std::string firstNames[10] = {"carlos", "rui", "sofia", "luis","bruno", "jorge","miguel","ze", "alexandre", "diogo"};
	
	
	vector<User *> users;
	User * realUser = new User();
	realUser->email = email;

	users.push_back(realUser);
	graph->users.push_back(realUser);
	RelationshipTag * family = new RelationshipTag();
	family->id = 1;
	family->name = "Familia";
	RelationshipTag * friends = new RelationshipTag();
	friends->name = "Amigos";
	friends->id = 2;
	RelationshipTag * con = new RelationshipTag();
	con->name = "Conhecidos";
	con->id = 3;
	RelationshipTag * relationShipTags[3] = {family, friends,con};
	for (int i = 0; i < 3; i++){
		graph->relationShipTags.push_back(relationShipTags[i]);
	}

	graph->users.push_back(realUser);
	srand(time(0));
	//Build Users and Direct RelationShips
	for(int i = 0; i < graphDepth; i++){
		vector<User *> tempUsers;
		while (!users.empty()){
			User * user = users.back();
			users.pop_back();
			int directConnections = 1+ rand() % 4 ;
			for (int y = 0; y < directConnections; y++){
				User * tempUser = new User();
			
				tempUser->email = firstNames[rand() % 5] + to_string(rand() % 100) + "@test.com";
				graph->users.push_back(tempUser);
				Relationship * relationShip = new Relationship();
				RelationshipTag * relationShipTag = relationShipTags[rand() % 3];
				relationShip->relationshipTag = relationShipTag;
				relationShip->strength = 1 + rand() % 5;
				relationShip->userA = user;
				relationShip->userB = tempUser;
				user->relationships.push_back(relationShip);
				tempUser->relationships.push_back(relationShip);
				tempUsers.push_back(tempUser);
			}
		}
		users = tempUsers;
	}
	int nonDirectRelationShips = graphDepth * rand() % 3;
	for (int i = 0; i < nonDirectRelationShips; i++){
		Relationship * relationShip = new Relationship();
		RelationshipTag * relationShipTag = relationShipTags[rand() % 3];

		User * userA = graph->users.at(rand() % graph->users.size());
		User * userB = NULL;
		while (userB == NULL || userA == userB)
		{
			User * userB = graph->users.at(rand() % graph->users.size());
			relationShip->strength = 1 + rand() % 5;
		}
		
	}

	for each(Relationship * r in graph->relationShips){
		int i = 0;
		r->glId = i++;
	}

	for each(User * u in graph->users){
		int i = 0;
		u->glId = i++;
	}

	graph->user = realUser;
	graphCoordWalker coordWalker;
	coordWalker.walk(graph->user);
	graph->maxConnectionStrenght = coordWalker.getMaxConnectionStrenght();
	graph->maxUserConnections = coordWalker.getMaxUserConnections();
	return graph;
}

Graph * GraphFactory::convertGraph(ns5__Graph * graph, string email){
	Graph * graphObj = new Graph();

	for (unsigned int i = 0; i < graph->RelationshipTags->RelationshipTag.size(); i++){
		ns5__RelationshipTag * ns5__relationshipTag = graph->RelationshipTags->RelationshipTag.at(i);
		RelationshipTag * relationshipTag = new RelationshipTag();
		relationshipTag->id = *ns5__relationshipTag->Id;
		relationshipTag->name = *ns5__relationshipTag->Name;
		graphObj->relationShipTags.push_back(relationshipTag);
	}

	for (unsigned int i = 0; i < graph->HumourStatus->HumourStatus.size(); i++){
		ns5__HumourStatus * ns5__humourStatus = graph->HumourStatus->HumourStatus.at(i);
		HumorStatus * humorStatusTemp = new HumorStatus();
		humorStatusTemp->id = *ns5__humourStatus->Id;
		humorStatusTemp->name = *ns5__humourStatus->Name;
		graphObj->humorStatus.push_back(humorStatusTemp);
	}

	for (unsigned int i = 0; i < graph->Interests->Interest.size(); i++){
		ns5__Interest * ns5__interest = graph->Interests->Interest.at(i);
		UserTag * userTag = new UserTag();
		userTag->id = *ns5__interest->Id;
		userTag->name = *ns5__interest->Name;
		graphObj->userTags.push_back(userTag);
	}

	for (unsigned int i = 0; i < graph->Users->User.size(); i++){
		ns5__User * ns5__user = graph->Users->User.at(i);
		User * user = new User();
		user->glId = i;
		user->email = *ns5__user->Email;

		if (ns5__user->Name != NULL){
			user->name = *ns5__user->Name;
		}
		if (ns5__user->Surname != NULL){
			user->surname = *ns5__user->Surname;
		}
		user->humor = graphObj->getHumorStatus(*ns5__user->HumourStatusId);
		for (int i = 0; i < graph->Interests->Interest.size(); i++){
			UserTag * userTag = graphObj->getUserTag(*graph->Interests->Interest.at(i)->Id);
			user->userTags.push_back(userTag);
		}

		graphObj->users.push_back(user);
	}

	for (unsigned int i = 0; i < graph->Relationships->Relationship.size(); i++){
		ns5__Relationship * ns5__relationship = graph->Relationships->Relationship.at(i);
		Relationship * relationship = new Relationship();
		User * userA = graphObj->getUser(*ns5__relationship->UserAEmail);
		User * userB = graphObj->getUser(*ns5__relationship->UserBEmail);
		RelationshipTag * relationshipTag = graphObj->getRelationshipTag(*ns5__relationship->RelationshipTagId);
		relationship->glId = i;
		relationship->userA = userA;
		relationship->userB = userB;
		relationship->strength = *ns5__relationship->Strength;
		relationship->relationshipTag = relationshipTag;
		userA->relationships.push_back(relationship);
		userB->relationships.push_back(relationship);
		graphObj->relationShips.push_back(relationship);
	}

	graphObj->user = graphObj->getUser(email);
	graphCoordWalker coordWalker;
	coordWalker.walk(graphObj->user);
	graphObj->maxConnectionStrenght = coordWalker.getMaxConnectionStrenght();
	graphObj->maxUserConnections = coordWalker.getMaxUserConnections();
	return graphObj;

}