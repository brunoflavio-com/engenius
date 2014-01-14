#include "PrologEngine.h"


PrologEngine::PrologEngine()
{
	char* argv[] = { "libswipl.dll", "-s", "SocialGameClient.pl", NULL };
	swiprolog = new PlEngine(3, argv);
}

PrologEngine::~PrologEngine(){
	delete swiprolog;
}

PlEngine * PrologEngine::getEngine() {
	return swiprolog;
}
PrologEngine& PrologEngine::getInstance()
{
	static PrologEngine    instance;
	return instance;
}