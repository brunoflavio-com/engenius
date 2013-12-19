#include "GraphWalkerDraw.h"


GraphWalkerDraw::GraphWalkerDraw()
{
}


GraphWalkerDraw::~GraphWalkerDraw()
{
}

void GraphWalkerDraw::walkConnection(User * userA, Relationship * relationship, int position, int total){
	//glBegin(GL_POLYGON);

	//GLUquadricObj *quadric;
	//glPushMatrix();

	//quadric = gluNewQuadric();
	//gluQuadricDrawStyle(quadric, GLU_FILL);
	//
	//
	//gluCylinder(quadric, .5, .5, 2, 30, 10);
	//glTranslatef(userA->x, userA->y, userA->z);

	//glPopMatrix();

	////glColor3f(0, 0, 1);
	////gluSphere(quadric, 1, 30, 10);
	////glRotatef(-135, 0, 1, 0);
	////gluCylinder(quadric, .5, .5, 2, 30, 10);

	//glEnd();

}

void GraphWalkerDraw::walkVertice(User * userA){

	

	

	GLUquadricObj *quadric;
	glPushMatrix();
	glTranslatef(userA->x, userA->y, userA->z);

	glBegin(GL_POLYGON);
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, 1, 30, 10);
	glTranslatef(userA->x, userA->y, userA->z);
	glColor3ub( rand()%255, rand()%255, rand()%255 );
	//glTranslatef(2, 0, 2);
	glEnd();
	glPopMatrix();

	//glColor3f(0, 0, 1);
	//gluSphere(quadric, 1, 30, 10);
	//glRotatef(-135, 0, 1, 0);
	//gluCylinder(quadric, .5, .5, 2, 30, 10);

	
}