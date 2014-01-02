#include "graphCoordWalker.h"
#include <iostream>

#define MIN_DIST 7.5
#define SPHERE_RADIUS 2

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
	
	/*Reset Stats*/
	maxStrenght = 0;
	maxUserConnections = 0;

	std::cout << graph->email << " | ";
	std::cout << graph->x << " | ";
	std::cout << graph->y << " | ";
	std::cout << graph->z << " | ";
	std::cout << graph->graphLevel << endl;
	GraphWalker::walk(graph);
}

void graphCoordWalker::walkVertice(User * user){
	//Sets Height to the number of connections:
	user->z = user->relationships.size();
	/*Update Stats*/
	maxUserConnections = user->z > maxUserConnections? user->z : maxUserConnections;
}

void graphCoordWalker::walkConnection(User * userA, Relationship * relationship, int position, int total){
	if (relationship->user->graphLevel == -1){
		relationship->user->graphLevel = userA->graphLevel + 1;
		User * userB = relationship->user;
		float racio = position / (float)total;
		int totalRelationships = userA->relationships.size();
		float distance, sx, sy;

		distance = MIN_DIST - ((3 * 2 * SPHERE_RADIUS) + totalRelationships *(2 * SPHERE_RADIUS)) / (2 * M_PI);

		if (userB->graphLevel == 2){ // Level 2 positions
			double prevAngle;
			if (userA->x < 0) // in case the X is negtive
				prevAngle = atan2(userA->y, userA->x) + M_PI - M_PI/4;
			else
				prevAngle = atan2(userA->y, userA->x) - M_PI/4;

			sx = ((MIN_DIST + distance)*cos(prevAngle + ((M_PI / 2)*position / totalRelationships)));
			sy = ((MIN_DIST + distance)*sin(prevAngle + ((M_PI / 2)*position / totalRelationships)));
		}
		else{ // Level 1 positions
			sx = ((MIN_DIST + distance)*cos(2 * M_PI*position / totalRelationships));
			sy = ((MIN_DIST + distance)*sin(2 * M_PI*position / totalRelationships));
		}
		//float sx = floorf(cos(2 * M_PI * racio) * 100) / 100 * 3*(3 - userB->graphLevel);
		//float sy = floorf(sin(2 * M_PI * racio) * 100) / 100 * 3*(3 - userB->graphLevel);
		

		/*Update Stats*/
		maxStrenght = relationship->strength > maxStrenght ? relationship->strength : maxStrenght;

		userB->x= userA->x + sx;
		userB->y = userA->y + sy;
		//Z definido no walkVertice() 
		//userB->z = 0;

		std::cout << userB->email << " | ";
		std::cout << userB->x << " | ";
		std::cout << userB->y << " | ";
		std::cout << userB->z << " | ";
		std::cout << userB->graphLevel << endl;
	}
}

int graphCoordWalker::getMaxConnectionStrenght() {
	return maxStrenght;
}

int graphCoordWalker::getMaxUserConnections() {
	return maxUserConnections;
}
