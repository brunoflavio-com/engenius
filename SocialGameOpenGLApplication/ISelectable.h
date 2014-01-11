#pragma once
#include <string>

class ISelectable
{
	
private:
	
public:
	static const int USER_TYPE = 1;
	static const int RELATIONSHIP_TYPE = 2;
	bool selected;
	virtual int getType()=0;
	ISelectable();
	~ISelectable();
	virtual std::string toString() = 0;

};

