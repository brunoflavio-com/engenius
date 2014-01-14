#pragma once
#include <SWI-cpp.h>
#include <string>

#define PRIZE 500

using namespace std;

class HangmanPLEngine
{
public:
	HangmanPLEngine(int maxRetries, string word);
	~HangmanPLEngine();

	//Verify gameover
	bool isGameOver();

	//Player win?
	bool isWinner();
	
	//number of tries
	int noOfRetries();

	string getMessage();

	//play guess 
	void play(char attempt);

	//clear data
	void clear();

private:
	PlEngine * prolog;
	int maxRetries;
	int curRetries;

	bool gameOver;
	bool winner;

	string message;
	string word;

	//prolog assert word
	void setWord(string word);

	//from prolog predicate find, and assert attempt
	//1 - word contains character;
	//2 - word does not contains character.
	//3 - character repeated
	int plPlay(char attempt);

	//Verify if there is a winner (Win - 0; otherwise -1)
	int plWinner();

};

