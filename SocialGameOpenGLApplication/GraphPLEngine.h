#pragma once
#include <SWI-cpp.h>
#include <vector>
#include <string>

using namespace std;

class GraphPLEngine
{
public:

	GraphPLEngine();
	~GraphPLEngine();

	void assertRelationship(string origin, string destination, int strenght);

	vector<string> getShortestPath(string origin, string destination);
	vector<string> getStrongestPath(string origin, string destination);

private:
	PlEngine * prolog;
	vector<string> getPath(string origin, string destination, string predicate);
};

