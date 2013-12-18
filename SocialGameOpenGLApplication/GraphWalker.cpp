#include "GraphWalker.h"
#include <iostream>

GraphWalker::GraphWalker()
{
}


GraphWalker::~GraphWalker()
{
}

void GraphWalker::walk(User * graph){
	visitedUsers.clear();
	users.clear();

	visitedUsers.push_back(graph);
	users.push_back(graph);
	
	while (!users.empty()){
		User * user = users.back();
		walkVertice(user);
		users.pop_back();
		for (int i = 0; i<user->relationships->size(); i++){
			User * tempUser = user->relationships->at(i)->user;
			walkConnection(user, user->relationships->at(i));
			if (std::find(visitedUsers.begin(), visitedUsers.end(),tempUser) == visitedUsers.end()){
				//User is not visited
				visitedUsers.insert(visitedUsers.begin(), user->relationships->at(i)->user);
				users.insert(users.begin(), user->relationships->at(i)->user);
			}
		}
	}	
}


