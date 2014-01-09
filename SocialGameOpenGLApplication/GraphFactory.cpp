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
				tempUsers.push_back(tempUser);
				graph->users.push_back(tempUser);
				tempUser->email = firstNames[rand() % 5] + to_string(rand() % 100) + "@test.com";
				Relationship * relationShip = new Relationship();
				graph->relationShips.push_back(relationShip);
				
				RelationshipTag * relationShipTag = relationShipTags[rand() % 3];
				relationShip->relationshipTag = relationShipTag;
				relationShip->strength = 1 + rand() % 5;
				relationShip->userA = user;
				relationShip->userB = tempUser;
				user->relationships.push_back(relationShip);
				tempUser->relationships.push_back(relationShip);
				
			}
		}
		users = tempUsers;
	}
	int nonDirectRelationShips = rand() % graph->users.size();

	for (int i = 0; i < nonDirectRelationShips; i++){
		Relationship * relationShip = new Relationship();
		RelationshipTag * relationShipTag = relationShipTags[rand() % 3];
		relationShip->strength = 1 + rand() % 5;
		User * userA = graph->users.at(rand() % graph->users.size());
		User * userB = NULL;

		while (userB == NULL || userB == userA)
		{
		    userB = graph->users.at(rand() % graph->users.size());
			for each(Relationship * r in graph->relationShips){
				if (r->contains(userA) && r->contains(userB)){
					userB = NULL;
				}
				
			}
		}
		relationShip->userA = userA;
		relationShip->userB = userB;
		userA->relationships.push_back(relationShip);
		userB->relationships.push_back(relationShip);
		graph->relationShips.push_back(relationShip);
	}
	int maxUserRelationShips = 0;
	for (int i = 0; i < graph->users.size();i++){
		graph->users.at(i)->glId = i;
		if (maxUserRelationShips < graph->users.at(i)->relationships.size()){
			maxUserRelationShips = graph->users.at(i)->relationships.size();
		}

	}

	int maxRelationStrength = 0;
	for (int i = 0; i < graph->relationShips.size(); i++){
		graph->relationShips.at(i)->glId = i;
		if (maxRelationStrength < graph->relationShips.at(i)->strength){
			maxRelationStrength = graph->relationShips.at(i)->strength;
		}
	}

	graph->user = realUser;
	graph->maxConnectionStrenght = maxRelationStrength;
	graph->maxUserConnections = maxUserRelationShips;

	graphCoordWalker coordWalker(maxUserRelationShips, maxRelationStrength);
	coordWalker.walk(graph->user);
	graph->user->isCenter = true;
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
	graphObj->user->isCenter = true;
	int maxUserRelationShips= 0;
	for (int i = 0; i < graphObj->users.size(); i++){
		graphObj->users.at(i)->glId = i;
		if (maxUserRelationShips < graphObj->users.at(i)->relationships.size()){
			maxUserRelationShips = graphObj->users.at(i)->relationships.size();
		}

	}

	int maxRelationStrength = 0;
	for (int i = 0; i < graphObj->relationShips.size(); i++){
		graphObj->relationShips.at(i)->glId = i;
		if (maxRelationStrength < graphObj->relationShips.at(i)->strength){
			maxRelationStrength = graphObj->relationShips.at(i)->strength;
		}
	}

	graphObj->maxConnectionStrenght = maxRelationStrength;
	graphObj->maxUserConnections = maxUserRelationShips;

	graphCoordWalker coordWalker(maxUserRelationShips, maxRelationStrength);
	coordWalker.walk(graphObj->user);
	return graphObj;

}