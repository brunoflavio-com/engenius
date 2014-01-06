#pragma once
#include <vector>

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
		bool isWall(int line, int column);
	
	private:
		vector<vector<char>*>* mapMatrix;

		//Initial Position
		int startLine;
		int startColumn;

		void readMapFile(string mapFile);
	};
}

