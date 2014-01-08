#include "MazeMap.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace MinigamesMaze;

MazeMap::MazeMap()
{
	this->mapMatrix = new std::vector<vector<char>*>();
}

MazeMap::MazeMap(string mapFile){
	this->mapMatrix = new std::vector<vector<char>*>();
	this->game = new MazePlEngine();

	/*This function must be called after the PlEngine be initialized*/
	this->readMapFile(mapFile);
}


MazeMap::~MazeMap()
{
	delete this->mapMatrix;
	delete this->game;
}

int MazeMap::getHeight()
{
	return this->mapMatrix->size();
}

int MazeMap::getWidth()
{
	return this->mapMatrix->at(0)->size();
}

int MazeMap::getStartLine()
{
	return startLine;
}

int MazeMap::getStartColumn()
{
	return startColumn;
}

void MazeMap::setCurrentPosition(int line, int column)
{
	this->currentLine = line;
	this->currentColumn = column;
}

void MazeMap::getSuggestion(int& sugLine, int& sugColumn)
{
	game->getSuggestion(currentLine, currentColumn, goalLine, goalColumn, sugLine, sugColumn);
}

bool MazeMap::isWall(int x, int y)
{
	if (x >= 0 && x < this->mapMatrix->size())
	{
		if (y >= 0 && y < this->mapMatrix->at(x)->size())
		{
			return (this->mapMatrix->at(x)->at(y) == 1) ? true : false;
		}
	}
	return false;
}

/*Private*/

void MazeMap::readMapFile(string mapFile){
	std::ifstream file;
	string fileLine;

	file.open(mapFile);
	while (!file.eof())
	{
		vector<char>* matrixLine = new vector<char>();
		this->mapMatrix->push_back(matrixLine);

		std::getline(file, fileLine);
		for (int i = 0; i < fileLine.size(); i++){
			if (fileLine[i] == '*'){
				matrixLine->push_back(1);
			}
			else{
				matrixLine->push_back(0);
				game->setNode(mapMatrix->size() - 1, matrixLine->size() - 1);
				if (fileLine[i] == '+'){
					startLine = currentLine = mapMatrix->size() - 1;
					startColumn = currentColumn = matrixLine->size() - 1;
				}
				if (fileLine[i] == 'x'){
					goalLine = mapMatrix->size() - 1;
					goalColumn = matrixLine->size() - 1;
				}
			}
		}
	}

	for (int i = 0; i < mapMatrix->size(); i++){
		vector<char>* line = mapMatrix->at(i);
		for (int j = 0; j < line->size(); j++){
			std::cout << (int)line->at(j) << ",";
		}
	}
}
