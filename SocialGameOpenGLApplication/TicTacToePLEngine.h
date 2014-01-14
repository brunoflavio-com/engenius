#pragma once
#include <SWI-cpp.h>
#include <string>

using namespace std;

class TicTacToePLEngine
{
public:

	// PL Engine, Define first player as human (o- human;x-computer)
	TicTacToePLEngine(char Player);
	~TicTacToePLEngine();

	//Get Message
	string getMessage();

	// Get Computer Move
	void playTTT(int square);
	int getComputerMove();
	int getStatus();
	void setHumanMove(int square);

	void clear();
	
private:
	PlEngine * prolog;

	// Winner:1 - Human; 2 - Computer; 
	int winner;
	int status;

	string message;

	// Prepare the Tic tac Toe Game, initialize board and set first player ( x - Computer; o - Human)
	void plSetFirstPlayer(char symbol);

	// Human Move where Square:[1-9] ; return status game( 2- computer wins; 1- human wins; 3- draw; -1 -playing)
	int plHumanPlay(int square);
	
	// Best Computer move, return Square [1-9]
	int plComputerPlay();

	// Verify status game: return status game( 2- computer wins; 1- human wins; 3- draw; -1 -playing)
	int plStatusGame();

	
};

