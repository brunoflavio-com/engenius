#include "User.h"
#include <gl\freeglut.h>

#define SPHERE_RADIUS 2

User::User()
{
	graphLevel = -1;
/*	cota = 0;
	x = 0;
	y = 0;
	z = 0; */
	isTarget = false;
	isCenter = false;
	selected = false;
}


User::~User()
{
}

int User::getType(){
	return USER_TYPE;
}