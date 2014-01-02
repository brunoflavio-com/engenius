#include "Graph.h"
#include "graphCoordWalker.h"
#include "GraphWalkerDraw.h"

Graph::Graph(ns5__Graph * graph, std::string email)
{
	user = converter.convertGraph(graph, email);
	graphCoordWalker coordWalker;
	coordWalker.walk(user);

	maxConnectionStrenght = coordWalker.getMaxConnectionStrenght();
	maxUserConnections = coordWalker.getMaxUserConnections();
}
void Graph::draw(){
	GraphWalkerDraw drawWalker(maxUserConnections, maxConnectionStrenght);
	drawWalker.walk(user);
}

Graph::~Graph()
{
	for each (User * var in converter.users)
	{
		delete var;
	}

	for each (HumorStatus * var in converter.humorStatus)
	{
		delete var;
	}

	for each (RelationshipTag * var in converter.relationShipTags)
	{
		delete var;
	}

	for each (Relationship * var in converter.relationShips)
	{
		delete var;
	}

	for each (UserTag * var in converter.userTags)
	{
		delete var;
	}
}
