#include "User.h"
#include <gl\freeglut.h>

#define SPHERE_RADIUS 2

User::User()
{
	graphLevel = -1;
	isTarget = false;
}


User::~User()
{
}

int User::getType(){
	return USER_TYPE;
}