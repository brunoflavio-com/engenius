#pragma once
#include "User.h"
#include <vector>
class GraphWalker
{
private:
	vector<User *> visitedUsers ;
	vector<User *> users;
protected:
	virtual void walkConnection(User * userA, Relationship * relationship) = 0;
	virtual void walkVertice(User * userA) = 0;
public:

	GraphWalker();
	virtual void walk(User * graph);
	~GraphWalker();
	
};

