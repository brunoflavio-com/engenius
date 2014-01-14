#pragma once
#include <SWI-cpp.h>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;

class GraphPLEngine
{
public:

	GraphPLEngine();
	~GraphPLEngine();

	void loadGraph(Graph * graph);
	void assertRelationship(string origin, string destination, int strenght);
	void clearRelationships();

	vector<Relationship *> getShortestPath(User * origin, User * destination);
	vector<Relationship *> getStrongestPath(User * origin, User * destination);

private:
	PlEngine * prolog;
	Graph * graph;

	vector<string> getPath(string origin, string destination, string predicate);
	vector<Relationship *> getRelationships(vector<string> path_user_email);

	vector<string> getShortestPath_user_email(string origin, string destination);
	vector<string> getStrongestPath_user_email(string origin, string destination);
};

