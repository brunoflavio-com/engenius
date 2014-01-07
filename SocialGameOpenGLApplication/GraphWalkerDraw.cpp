#include "GraphWalkerDraw.h"
#include <iostream>
#include <gl\freeglut.h>
#include <string>

#define M_PI 3.1415926535897932384626433832795
#define RAD(x)          (M_PI*(x)/180)
#define DEG(x)        (180*(x)/M_PI)

#define SPHERE_RADIUS 2
#define MAX_HEIGHT 5


GraphWalkerDraw::GraphWalkerDraw(int maxUserConnections, int maxConnectionStrenght, bool drawUserNames)
{
	this->maxUserConnections = maxUserConnections;
	this->maxConnectionStrenght = maxConnectionStrenght;	
	this->drawUserNames = drawUserNames;
}


GraphWalkerDraw::~GraphWalkerDraw()
{
}

void GraphWalkerDraw::walkConnection(User * userA, Relationship * relationship, int position, int total){
	User * userB = relationship->getDestinationUser(userA);

	/*Adjust height to max_height*/
	float Za = MAX_HEIGHT * userA->z / maxUserConnections;
	float Zb = MAX_HEIGHT * userB->z / maxUserConnections;

	/*Adjust cylinder radios to max_cylinder_radius*/
	float cylinderRadius = SPHERE_RADIUS * 0.75 * relationship->strength / maxConnectionStrenght;
	GLUquadricObj *quadric;

	float deltaX = userB->x - userA->x;
	float deltaY = userB->y - userA->y;
	float deltaZ = Zb-Za;

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
	glLoadName((GLuint)relationship);
	glPushMatrix();
		glTranslatef(userA->x, userA->y, Za);

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

	/*Adjust height to max_height*/
	float Z = MAX_HEIGHT * userA->z / maxUserConnections;
	
	GLUquadricObj *quadric;
	glPushMatrix();
	glTranslatef(userA->x, userA->y, Z);

	//We'll use the address of this node as the gl Identifier:
	glLoadName((GLuint) userA);
	if (glRenderMode)
		quadric = gluNewQuadric();

	if (userA->selected) selectedAttribute();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, SPHERE_RADIUS, 30, 10);
	if (userA->selected) glPopAttrib();

	//User text
	if (drawUserNames && userA->selected){
		glDisable(GL_LIGHTING);
		glColor3ub(200, 200, 200);
		glRasterPos3f(-2, 0, 4);

		unsigned char s[100];

		strcpy((char*)s, userA->email.c_str());

		glutBitmapString(GLUT_BITMAP_HELVETICA_12, s);
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();


	/*DEBUG:*/
	//std::cout << "(" << userA->x << "," << userA->y << "," << userA->z << ")" << endl;
}


void GraphWalkerDraw::selectedAttribute(void)
{
	static GLfloat red[4] =
	{ 1.0, 0.0, 0.0, 1.0 };

	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glColor3f(1.0, 0.0, 0.0);
}