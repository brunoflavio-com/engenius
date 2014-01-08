#pragma once
#include "ISelectable.h"
#include "Relationship.h"
#include "UserTag.h"
#include "HumorStatus.h"
#include <vector>
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

	 vector<Relationship *>  relationships;
	 vector<UserTag *>  userTags;
	 HumorStatus * humor;
	 int getType();
	User();
	~User();
};

