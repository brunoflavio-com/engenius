#include "GraphPLEngine.h"
#include "PrologEngine.h"

GraphPLEngine::GraphPLEngine()
{	
	this->prolog = PrologEngine::getInstance().getEngine();	
}

GraphPLEngine::~GraphPLEngine()
{
}

void GraphPLEngine::loadGraph(Graph * graph)
{
	clearRelationships();
	this->graph = graph;
	for each(Relationship * r in graph->relationShips) {
		assertRelationship(r->userA->email, r->userB->email, r->strength);
	}
}

void GraphPLEngine::clearRelationships() {
	
	PlQuery	plClear("cleargraph", NULL);
	plClear.next_solution();

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

vector<string> GraphPLEngine::getShortestPath_user_email(string origin, string destination){
	return getPath(origin, destination, "find_shortest_path");
}

vector<string> GraphPLEngine::getStrongestPath_user_email(string origin, string destination){
	return getPath(origin, destination, "find_strongest_path");
}


vector<Relationship *> GraphPLEngine::getShortestPath(User * origin, User * destination){
	return getRelationships(getShortestPath_user_email(origin->email, destination->email));
}

vector<Relationship *> GraphPLEngine::getStrongestPath(User * origin, User * destination){
	
	return getRelationships(getStrongestPath_user_email(origin->email, destination->email));
}

vector<Relationship *> GraphPLEngine::getRelationships(vector<string> path_user_email){
	vector<Relationship *> path;

	for (int i = 0; i < path_user_email.size() - 1; ++i){
		User * userA = graph->getUser(path_user_email.at(i));
		User * userB = graph->getUser(path_user_email.at(i + 1));
		Relationship * relationship = graph->getRelationship(userA, userB);
		path.push_back(relationship);
	}

	return path;
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