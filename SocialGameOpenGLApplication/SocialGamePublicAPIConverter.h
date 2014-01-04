#pragma once
#include "User.h"
#include "Relationship.h"
#include "RelationshipTag.h"
#include "HumorStatus.h"
#include "UserTag.h"
#include <string>
#include "gsoapAPIClient\soapBasicHttpBinding_USCOREISocialGameServiceProxy.h"
#include <vector>

class SocialGamePublicAPIConverter
{
	
public:
	vector<User *> users;
	vector<Relationship * > relationShips;
	vector<RelationshipTag * > relationShipTags;
	vector<HumorStatus * > humorStatus;
	vector<UserTag * > userTags;
	User * convertGraph(ns5__Graph * graph, string email);
	UserTag * getUserTag(int id);
	User * getUser(string email);
	HumorStatus *  getHumorStatus(int id);
	RelationshipTag *  SocialGamePublicAPIConverter::getRelationshipTag(int id);
	SocialGamePublicAPIConverter();
	~SocialGamePublicAPIConverter();
};

