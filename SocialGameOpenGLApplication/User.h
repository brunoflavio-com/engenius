#pragma once
#include <gl\glut.h>
#include "ISelectable.h"
#include "Relationship.h"
#include "UserTag.h"
#include "HumorStatus.h"
#include <vector>
#include <string>
class Relationship;

using namespace std;

class User : 
	public ISelectable
{
public:
	int glId;
	int graphLevel;
	string  email;
	string  name;
	string  surname;
	float cota;
	float x, y, z;
	bool isCurrentRealUser;
	bool isTarget;
	bool isCenter;
	bool canWalkThrough;
	float size;
	vector<Relationship *>  relationships;
	vector<UserTag *>  userTags;
	HumorStatus * humor;
	int getType();
	std::string toString();
	User();
	~User();
};

