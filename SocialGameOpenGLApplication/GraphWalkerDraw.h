#pragma once
#include "GraphWalker.h"
#include <gl\glut.h>

class GraphWalkerDraw :
	public GraphWalker
{
public:
	GraphWalkerDraw(int maxUserConnections, int maxConnectionStrenght);
	~GraphWalkerDraw();
	void walkConnection(User * userA, Relationship * relationship, int position, int total);
	void walkVertice(User * userA);
private:
	int maxUserConnections;
	int maxConnectionStrenght;
};

