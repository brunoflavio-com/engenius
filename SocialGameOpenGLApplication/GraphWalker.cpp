#include "GraphWalker.h"
#include <iostream>

GraphWalker::GraphWalker()
{
}


GraphWalker::~GraphWalker()
{
}

void GraphWalker::walk(User * graph, int graphDepth){
	//if GraphLevel = -1 means inicial walk, users dont have graphDepth specified 
	vector<User *> visitedUsers;
	vector<User *> users;

	visitedUsers.push_back(graph);
	users.push_back(graph);

	while (!users.empty()){
		User * user = users.back();
		walkVertice(user);
		users.pop_back();
		for (int i = 0; i < user->relationships.size(); i++){
			User * tempUser = user->relationships.at(i)->user;
			if (graphDepth == -1 || tempUser->graphLevel < graphDepth)
			{
				walkConnection(user, user->relationships.at(i), i, user->relationships.size());

				if (std::find(visitedUsers.begin(), visitedUsers.end(), tempUser) == visitedUsers.end()){
					//User is not visited

					visitedUsers.insert(visitedUsers.begin(), tempUser);
					users.insert(users.begin(), tempUser);
				}
			}
		}
	}
}


