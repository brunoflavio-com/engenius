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
	graph->x = 0;
	graph->y = 0;
	graph->z = 0;
	GraphWalker::walk(graph);
}

void graphCoordWalker::walkVertice(User * user){

}

void graphCoordWalker::walkConnection(User * userA, Relationship * relationship, int position, int total){
	if (relationship->user->graphLevel == -1){
		relationship->user->graphLevel = userA->graphLevel + 1;
		User * userB = relationship->user;
		float racio = position / (float)total;
		
		float sx = floorf(cos(2 * M_PI * racio) * 100) / 100 *2;
		float sy = floorf(sin(2 * M_PI * racio) * 100) / 100 * 2;

		userB->x= userA->x + sx;
		userB->y = userA->y + sy;
		userB->z = 0;

		std::cout << *userB->email << endl;
		std::cout << userB->x<<endl;
		std::cout << userB->y << endl;
		std::cout << userB->z << endl;
		std::cout << userB->graphLevel << endl;
	}
}
