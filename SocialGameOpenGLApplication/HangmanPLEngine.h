#pragma once
#include <SWI-cpp.h>
#include <string>

using namespace std;

class HangmanPLEngine
{
public:
	HangmanPLEngine(int maxRetries, string word);
	~HangmanPLEngine();

	bool isGameOver();	

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
	int plPlay(char attempt);
	int plWinner();

};

