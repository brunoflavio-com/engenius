#include "MazePlEngine.h"
#include "PrologEngine.h"
#include <iostream>

using namespace MinigamesMaze;

MazePlEngine::MazePlEngine()
{
	prolog = this->prolog = PrologEngine::getInstance().getEngine();
}


MazePlEngine::~MazePlEngine()
{
	clear();
}


void MazePlEngine::clear() {

	PlQuery	plClear("clearmaze", NULL);
	plClear.next_solution();

}


void MazePlEngine::setNode(int line, int column)
{
	PlTermv node_params(2);
	node_params[0] = line;
	node_params[1] = column;

	PlQuery set_node("set_node", node_params);
	std::cout << "node(" << line << "," << column << ")" << std::endl;
	set_node.next_solution();
}

void MazePlEngine::getSuggestion(int originLine, int originColumn, int destinyLine, int destinyColumn, int& SugLine, int& SugColumn)
{
	PlTermv suggestion_params(6);
	suggestion_params[0] = originLine;
	suggestion_params[1] = originColumn;
	suggestion_params[2] = destinyLine;
	suggestion_params[3] = destinyColumn;


	PlQuery suggestion("path", suggestion_params);
	suggestion.next_solution();
	SugLine = suggestion_params[4];
	SugColumn = suggestion_params[5];
}