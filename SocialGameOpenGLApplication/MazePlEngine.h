#pragma once
#include <SWI-cpp.h>
#include <string>
namespace MinigamesMaze{
	
	class MazePlEngine
	{
	public:
		MazePlEngine();
		~MazePlEngine();

		void setNode(int line, int column);

		void getSuggestion(int originLine, int originColumn, int destinyLine, int destinyColumn, int& SugLine, int& SugColumn);

	private:
		PlEngine* prolog;

	};

}

