#pragma once
#include <SWI-cpp.h>

class PrologEngine
{

public:
	static PrologEngine& getInstance();
	PlEngine * getEngine();
private:
		PrologEngine();
		~PrologEngine();

		PlEngine * swiprolog;

		//disallow copies.
		PrologEngine(PrologEngine const&);
		void operator=(PrologEngine const&);
};