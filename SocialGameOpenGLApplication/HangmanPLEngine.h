#pragma once
#include <SWI-cpp.h>
#include <string>

using namespace std;

class HangmanPLEngine
{
public:
	HangmanPLEngine(int maxRetries, string word);
	~HangmanPLEngine();

	bool isGameOver(bool &winner);	

	int noOfRetries();

	string getMessage();

	void play(char attempt);

private:
	PlEngine * prolog;
	int maxRetries;
	int curRetries;

	bool gameOver;
	bool winner;

	string message;
	
	void setWord(string word);
	bool hasWon();
	int plPlay(char attempt);

};

