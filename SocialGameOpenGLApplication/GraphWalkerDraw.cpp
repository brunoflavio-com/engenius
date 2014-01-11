#include "GraphWalkerDraw.h"
#include <iostream>
#include <gl\freeglut.h>
#include <string>

#define M_PI 3.1415926535897932384626433832795
#define RAD(x)          (M_PI*(x)/180)
#define DEG(x)        (180*(x)/M_PI)

#define SPHERE_RADIUS 2
#define MAX_HEIGHT 5
GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat red[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat blue[4] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat green[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat yellow[4] = { 1.0, 1.0, 0.0, 1.0 };

GraphWalkerDraw::GraphWalkerDraw(bool drawUserNames)
{	
	this->drawUserNames = drawUserNames;
}


GraphWalkerDraw::~GraphWalkerDraw()
{
}

void GraphWalkerDraw::walkConnection(User * userA, Relationship * relationship, int position, int total){
	User * userB = relationship->getDestinationUser(userA);

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
	float rotY = deltaX * deltaZ;

	glLoadName((GLuint)ISelectable::RELATIONSHIP_TYPE);
	glPushName((GLuint)relationship->glId);

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
		GLfloat * color = white;
		if (relationship->walked){
			color = red;
		}
		glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluCylinder(quadric, relationship->cylinderRadius, relationship->cylinderRadius, distance, 30, 3);
	    glPopAttrib();
	glPopMatrix();

	glPopName();
}

void GraphWalkerDraw::walkVertice(User * userA){

	/*Adjust height to max_height*/
	//float Z = MAX_HEIGHT * userA->z / maxUserConnections;
	
	GLUquadricObj *quadric;
	glPushMatrix();
	glTranslatef(userA->x, userA->y, userA->z);
 
	

	if (glRenderMode)
		quadric = gluNewQuadric();
	GLfloat * color = white;
	//Or
	if (userA->isTarget){
		color = green;
	}
	
	if (userA->isCurrentRealUser){
		color = yellow;
	}

	if (userA->isCenter){
		color = blue;
	}

	if (userA->selected) {
		color = red;

		if (drawUserNames){
			glDisable(GL_LIGHTING);
			glColor3ub(255, 255, 255);
			glRasterPos3f(-2, 0, 4);
			unsigned char s[100];
			strcpy((char*)s, userA->email.c_str());
			glutBitmapString(GLUT_BITMAP_HELVETICA_12, s);
			glEnable(GL_LIGHTING);
		}
	};

	glLoadName((GLuint)ISelectable::USER_TYPE);
	glPushName((GLuint)userA->glId);
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, SPHERE_RADIUS, 30, 10);
	glPopAttrib();
	glPopName();
	
	
	glPopMatrix();
}