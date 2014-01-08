#pragma once
#include "GraphWalker.h"

class GraphWalkerDraw :
	public GraphWalker
{
private:
public:
	GraphWalkerDraw(bool DrawUserName);
	~GraphWalkerDraw();
	void walkConnection(User * userA, Relationship * relationship, int position, int total);
	void walkVertice(User * userA);
	bool drawUserNames;

};

