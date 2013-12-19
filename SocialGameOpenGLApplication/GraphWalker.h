#pragma once
#include "User.h"
#include <vector>
class GraphWalker
{
private:
	
protected:
	virtual void walkConnection(User * userA, Relationship * relationship, int position, int total) = 0;
	virtual void walkVertice(User * userA) = 0;
public:

	GraphWalker();
	virtual void walk(User * graph);
	~GraphWalker();
	
};

