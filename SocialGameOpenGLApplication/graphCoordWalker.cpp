#include "graphCoordWalker.h"
#include <iostream>

graphCoordWalker::graphCoordWalker()
{
}


graphCoordWalker::~graphCoordWalker()
{
}

void graphCoordWalker::walk(User * graph){
	graph->graphLevel = 0;
	GraphWalker::walk(graph);
}

void graphCoordWalker::walkVertice(User * user){
	std::cout <<"\n-----------------\n" << *user->email<< " "<< user->graphLevel<<" - ";
}

void graphCoordWalker::walkConnection(User * userA, Relationship * relationship){
	if (relationship->user->graphLevel == -1){
		relationship->user->graphLevel = userA->graphLevel + 1;
	}
	std::cout << * relationship->user->email<<" ";
}
