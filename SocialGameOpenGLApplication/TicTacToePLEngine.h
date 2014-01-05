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
	int getComputerMove();
	int getStatus();
	
private:
	PlEngine * prolog;

	// Winner:1 - Human; 2 - Computer; 0 - Draw
	int winner;
	int status;

	string message;

	// Prepare the Tic tac Toe Game, initialize board and set first player ( x - Computer; o - Human)
	void plSetFirstPlayer(char symbol);

	// Human Move where Square:[1-9]
	int plHumanPlay(int square);
	
	// Best Computer move, return Square [1-9]
	int plComputerPlay();

	// Verify status game: return status game( 2- computer wins; 1- human wins; 0- draw; -1 -playing)
	int plStatusGame();

	
};

