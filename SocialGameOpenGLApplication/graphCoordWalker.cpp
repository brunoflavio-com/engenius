#include "graphCoordWalker.h"
#include <iostream>

#define MIN_DIST 7.5
#define SPHERE_RADIUS 2
#define MAX_HEIGHT 10

graphCoordWalker::graphCoordWalker(int maxUserRelationships, int maxStregth, int maxUserTags)
{
	this->maxUserConnections = maxUserRelationships;
	this->maxStrenght = maxStregth;
	this->maxUserTags = maxUserTags;
}


graphCoordWalker::~graphCoordWalker()
{
}

void graphCoordWalker::walk(User * graph){
	graph->graphLevel = 0;
	graph->x = 0;
	graph->y = 0;
	graph->z = MAX_HEIGHT *  graph->relationships.size() / maxUserConnections;
	graph->size = (graph->userTags.size()+1) / (float)(maxUserTags+1) ;
	GraphWalker::walk(graph,-1);
}

void graphCoordWalker::walkVertice(User * user){
	
}

void graphCoordWalker::walkConnection(User * userA, Relationship * relationship, int position, int total){
	User * userB = relationship->getDestinationUser(userA);
	if (userB->graphLevel == -1){
		userB->graphLevel = userA->graphLevel + 1;
		userB->size = (userB->userTags.size() + 1) /(float) (maxUserTags + 1) * SPHERE_RADIUS;
		float racio = position / (float)total;
		int totalRelationships = userA->relationships.size();
		float distance, sx, sy;

		distance = ((3 * 2 * SPHERE_RADIUS) + totalRelationships *(2 * SPHERE_RADIUS)) / (2 * M_PI);

		if (userB->graphLevel >= 2){ // Level 2 positions
			double prevAngle;
				prevAngle = atan2(userA->y, userA->x) - M_PI/4;

			sx = ((MIN_DIST + distance)*cos(prevAngle + ((M_PI / 2)*position / totalRelationships)));
			sy = ((MIN_DIST + distance)*sin(prevAngle + ((M_PI / 2)*position / totalRelationships)));
		}
		else{ // Level 1 positions
			sx = ((MIN_DIST + distance)*cos(2 * M_PI*position / totalRelationships));
			sy = ((MIN_DIST + distance)*sin(2 * M_PI*position / totalRelationships));
		}
		
		userB->x= userA->x + sx;
		userB->y = userA->y + sy;
		userB->z = MAX_HEIGHT *  userB->relationships.size() / maxUserConnections;

		
	}
	relationship->cylinderRadius = SPHERE_RADIUS * 0.75 * relationship->strength / maxStrenght;
}

int graphCoordWalker::getMaxConnectionStrenght() {
	return maxStrenght;
}

int graphCoordWalker::getMaxUserConnections() {
	return maxUserConnections;
}
