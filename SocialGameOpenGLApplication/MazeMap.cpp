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
	this->readMapFile(mapFile);
}


MazeMap::~MazeMap()
{
	delete this->mapMatrix;
}

int MazeMap::getHeight()
{
	return this->mapMatrix->size();
}

int MazeMap::getWidth()
{
	return this->mapMatrix->at(0)->size();
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
			if (fileLine[i] != ' '){
				matrixLine->push_back(1);
			}
			else{
				matrixLine->push_back(0);
			}
		}
	}

	for (int i = 0; i < mapMatrix->size(); i++){
		vector<char>* line = mapMatrix->at(i);
		for (int j = 0; j < line->size(); j++){
			std::cout << (int)line->at(j) << ",";
		}
		std::cout << std::endl;
	}
}
