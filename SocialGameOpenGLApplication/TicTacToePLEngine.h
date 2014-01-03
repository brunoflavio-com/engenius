#pragma once
#include <SWI-cpp.h>
#include <string>

#define HUMAN 'h'
#define COMPUTER 'c'

using namespace std;

class TicTacToePLEngine
{
public:


	// Status Game
	// status 2 -> computer wins
	// status 1 -> human wins
	// status 0 -> draw
	// status -1 -> playing
	int statusGame();
	char board[9];

	// Define first player as human
	TicTacToePLEngine(char Player=HUMAN);

	~TicTacToePLEngine();

	string getMessage();
	
private:
	PlEngine * prolog;

	// 1 - Human 	// 2 - Computer 	// 0 - Draw
	int winner;

	bool gameOver;
	string message;

	// Prepare the Tic tac Toe Game, initialize board and set first player
	// x -> Computer
	// o -> Human
	void setFirstPlayer(char symbol);

	// Human Move where Square:[1-9]
	void humanPlay(int square);
	
	// Best Computer move, return Square [1-9]
	void computerPlay();



	// Verify if game is over
	bool isGameOver();

	// Set Move
	void setMove(int square, char Player);

	//Play Game
	void playTTT();

};

