#include "GraphWalkerDraw.h"

#define M_PI 3.1415926535897932384626433832795
#define RAD(x)          (M_PI*(x)/180)
#define DEG(x)        (180*(x)/M_PI)



GraphWalkerDraw::GraphWalkerDraw()
{
}


GraphWalkerDraw::~GraphWalkerDraw()
{
}

void GraphWalkerDraw::walkConnection(User * userA, Relationship * relationship, int position, int total){
	User * userB = relationship->user;
	float cylinderRadius = relationship->strength * 0.1;
	GLUquadricObj *quadric;

	float deltaX = userB->x - userA->x;
	float deltaY = userB->y - userA->y;
	float deltaZ = userB->z - userA->z;

	float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));

	float rotAngle;
	if (fabs(deltaZ) <= 0.001)  {
			rotAngle = DEG(acos(deltaX / distance));
			if (deltaY <= 0.0)
				rotAngle *= -1;

	}
	else {
		rotAngle = DEG(acos(deltaZ / distance));
		if (deltaZ <= 0.0)
			rotAngle *= -1;
	}

	float rotX = -deltaY * deltaZ;
	float rotY =  deltaX * deltaZ;

	glPushMatrix();
		glTranslatef(userA->x, userA->y, userA->z);

		if (fabs(deltaZ) <= 0.001)  {
			glRotatef(90.0, 0 , 1, 0.0);
			glRotatef(rotAngle, -1.0, 0.0, 0.0);
		}
		else {
			glRotatef(rotAngle, rotX, rotY, 0.0);
		}

		quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluCylinder(quadric, cylinderRadius, cylinderRadius, distance, 30,10);
	glPopMatrix();

}

void GraphWalkerDraw::walkVertice(User * userA){

	GLUquadricObj *quadric;
	glPushMatrix();
	glTranslatef(userA->x, userA->y, userA->z);

	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, 1, 30, 10);
	glTranslatef(userA->x, userA->y, userA->z);
	glColor3ub( rand()%255, rand()%255, rand()%255 );	

	glPopMatrix();
}