#pragma once
#include <vector>
#include "MazePlEngine.h"

namespace MinigamesMaze{
	using namespace std;
	class MazeMap
	{
	public:
		MazeMap();
		MazeMap(string MapFile);
		~MazeMap();

		int getWidth();
		int getHeight();

		int getStartLine();
		int getStartColumn();

		void setCurrentPosition(int line, int column);

		void getSuggestion(int& line, int& column);

		bool isWall(int line, int column);
		bool isFinalPosition();
	
	private:
		vector<vector<char>*>* mapMatrix;
		MazePlEngine* game;

		//Initial Position
		int startLine;
		int startColumn;

		//Current Position
		int currentLine;
		int currentColumn;

		//Goal Position
		int goalLine;
		int goalColumn;

		void readMapFile(string mapFile);
	};
}

