#pragma once
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include "GraphWalker.h"
class GraphPositionWalker :
	public GraphWalker
{
public:
	GraphPositionWalker(int maxUserRelationships, int maxStregth, int maxUserTags);
	~GraphPositionWalker();
	void walkConnection(User * userA, Relationship * relationship, int position, int total);
	void walkVertice(User * userA);
	void walk(User * graph);
	int getMaxConnectionStrenght();
	int getMaxUserConnections();
	int getMaxUserTags();
private:
	int maxUserTags;
	int maxStrenght;
	int maxUserConnections;
};

