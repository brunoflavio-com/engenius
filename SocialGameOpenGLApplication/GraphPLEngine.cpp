#include "GraphPLEngine.h"


GraphPLEngine::GraphPLEngine()
{
	char* argv[] = { "libswipl.dll", "-s", "graph.pl", NULL };

	prolog = new PlEngine(3, argv);
	
}

GraphPLEngine::~GraphPLEngine()
{
	delete prolog;
}


void GraphPLEngine::assertRelationship(string origin, string destination, int strength){

	//prepare term for 3 parameters:
	PlTermv plAssertTerms(3);
	plAssertTerms[0] = PlAtom(origin.c_str());
	plAssertTerms[1] = PlAtom(destination.c_str());
	plAssertTerms[2] = strength;


	PlQuery	plAssert("insert", plAssertTerms);
	plAssert.next_solution();
}

vector<string> GraphPLEngine::getShortestPath(string origin, string destination){
	return getPath(origin, destination, "find_shortest_path");
}

vector<string> GraphPLEngine::getStrongestPath(string origin, string destination){
	return getPath(origin, destination, "find_strongest_path");
}

vector<string> GraphPLEngine::getPath(string origin, string destination, string predicate){
	//prepare term for 3 parameters (origin, destination, path):
	PlTermv plFindPathTerms(3);
	plFindPathTerms[0] = PlAtom(origin.c_str());
	plFindPathTerms[1] = PlAtom(destination.c_str());


	PlQuery	plFindPath(predicate.c_str(), plFindPathTerms);
	plFindPath.next_solution();

	vector<string> path;
	PlTail plPath(plFindPathTerms[2]);
	PlTerm plNode;
	while (plPath.next(plNode)){
		path.push_back((char *)plNode);
	}

	return path;
}