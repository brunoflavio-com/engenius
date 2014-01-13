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

	// Sample Data for random Generation
	std::string firstNames[10] = {"carlos", "rui", "sofia", "luis","bruno", "jorge","miguel","ze", "alexandre", "diogo"};
	std::string surnames[10] = { "Teixeira", "Silvino", "Moreira", "Novais", "Flavio", "Pinto", "Lima", "Mota", "Pessegueira", "Pereira" };

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


	UserTag * tag1 = new UserTag();
	tag1->id = 1;
	tag1->name = "Animais";
	UserTag * tag2 = new UserTag();
	tag2->id = 2;
	tag2->name = "Programação";
	UserTag * tag3 = new UserTag();
	tag3->id = 3;
	tag3->name = "Poker";

	UserTag * userTags[3] = { tag1, tag2, tag3 };

	for (int i = 0; i < 3; i++){
		graph->userTags.push_back(userTags[i]);
	}

	HumorStatus * ustatus1 = new HumorStatus();
	ustatus1->id = 1;
	ustatus1->name = "Happy";
	HumorStatus * ustatus2 = new HumorStatus();
	ustatus2->id = 2;
	ustatus2->name = "Normal";
	HumorStatus * ustatus3 = new HumorStatus();
	ustatus3->id = 3;
	ustatus3->name = "Sad";

	HumorStatus * uStatus[3] = { ustatus1, ustatus2, ustatus3 };

	for (int i = 0; i < 3; i++){
		graph->humorStatus.push_back(uStatus[i]);
	}

	vector<User *> users;
	User * realUser = new User();
	realUser->isCurrentRealUser = true;
	realUser->email = email;
	realUser->humor = uStatus[rand() % 3];
	users.push_back(realUser);
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
				
				string name = firstNames[rand() % 5];
				string surname = surnames[rand() % 5];
				tempUser->email =  name + to_string(rand() % 100) + surname+"@gmail.com";
				
				
				tempUser->name = name;
				tempUser->surname = surname;
				tempUser->humor = uStatus[rand() % 3];
				UserTag * uTag = userTags[rand() % 3];
				tempUser->userTags.push_back(uTag);
				tempUsers.push_back(tempUser);
				graph->users.push_back(tempUser);
				
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
	int nUsers = graph->users.size();
	int nonDirectRelationShips = rand() % nUsers;
	int maxConnectionPossible = nUsers*(nUsers - 1) / 2;

	for (int i = 0; i < nonDirectRelationShips; i++){
		if (maxConnectionPossible == graph->relationShips.size())
		{
			//There cannot be more connections when every user is connected
			break;
		}
		Relationship * relationShip = new Relationship();
		RelationshipTag * relationShipTag = relationShipTags[rand() % 3];
		relationShip->strength = 1 + rand() % 5;
		relationShip->relationshipTag = relationShipTag;
		User * userB = NULL;
		User * userA = NULL;

		
		while (userB == userA)
		{ 
			userA = graph->users.at(rand() % graph->users.size());
		    userB = graph->users.at(rand() % graph->users.size());
			//Checking if Relationship already exists
			for each(Relationship * r in graph->relationShips){
				if (r->contains(userA) && r->contains(userB)){
					userB = NULL;
					userA = NULL;
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
		for (int i = 0; i < graph->Users->User.at(i)->InterestsIDs->int_.size(); i++){
			UserTag * userTag = graphObj->getUserTag(graph->Users->User.at(i)->InterestsIDs->int_.at(i));
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
	graphObj->user = graphObj->getUser(email);
	graphObj->user->isCenter = true;
	graphCoordWalker coordWalker(maxUserRelationShips, maxRelationStrength);
	coordWalker.walk(graphObj->user);
	return graphObj;

}