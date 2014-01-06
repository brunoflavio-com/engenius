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
		bool isWall(int line, int column);
	
	private:
		vector<vector<char>*>* mapMatrix;

		void readMapFile(string mapFile);
	};
}

