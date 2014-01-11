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

string User::toString(){

	string tempString =
		"Email: " + email + "\n" +
	    "Name: " + name + "\n" +
		"Surname: " + surname + "\n" +
		"Humor status: " + humor->name + "\n" +
		"Tags: \n";
	for each(UserTag * tag in userTags){
		tempString += "     " + tag->name + "\n";
	}
	return tempString;

}