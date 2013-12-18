#pragma once
#include "GraphWalker.h"
class graphCoordWalker :
	public GraphWalker
{
public:
	graphCoordWalker();
	~graphCoordWalker();
	void walkConnection(User * userA, Relationship * relationship);
	void walkVertice(User * userA);
	void walk(User * graph);
};

