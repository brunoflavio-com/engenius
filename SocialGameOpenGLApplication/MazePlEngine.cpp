#include "MazePlEngine.h"
#include <iostream>

using namespace MinigamesMaze;

MazePlEngine::MazePlEngine()
{
	char* argv[] = { "libswipl.dll", "-s", "maze.pl", NULL};
	prolog = new PlEngine(3, argv);
}


MazePlEngine::~MazePlEngine()
{
	delete prolog;
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
	if (suggestion.next_solution()){
		std::cout << "Success";
		SugLine = suggestion_params[4];
		SugColumn = suggestion_params[5];
	}
	else{
		std::cout << "Failed";
	}
}