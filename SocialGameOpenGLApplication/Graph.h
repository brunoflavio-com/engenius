#pragma once
#include "User.h"
#include "gsoapAPIClient\soapBasicHttpBinding_USCOREISocialGameServiceProxy.h"
#include <string>
class Graph
{
private:

public:
	User * user;
	vector<User *> users;
	vector<Relationship * > relationShips;
	vector<RelationshipTag * > relationShipTags;
	vector<HumorStatus * > humorStatus;
	vector<UserTag * > userTags;
	int maxUserConnections;
	int maxConnectionStrenght;
	int maxUserTags;
	UserTag * getUserTag(int id);
	User * getUser(string email);
	HumorStatus *  getHumorStatus(int id);
	RelationshipTag *  getRelationshipTag(int id);
	Relationship * getRelationship(User * userA, User * userB);
	Graph();
	~Graph();
	void draw(bool drawUserName);
	void movetoVertice(User * user);
};

