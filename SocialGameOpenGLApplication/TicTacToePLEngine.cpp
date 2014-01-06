#include "TicTacToePLEngine.h"


TicTacToePLEngine::TicTacToePLEngine(char symbolFirstPlayer)
{
	
	char* argv [] = { "libswipl.dll", "-s", "tictactoe.pl", NULL };

	prolog = new PlEngine(3, argv);
	//plSetFirstPlayer(symbolFirstPlayer);

	message = "Hi, good luck playing Tic Tac Toe!\nYou Start!";

}

TicTacToePLEngine::~TicTacToePLEngine()
{
	delete prolog;
}

void TicTacToePLEngine::plSetFirstPlayer(char symbol)
{
	char plSymbol[2] = { symbol, '\0' };
	//prepare parameters:
	PlTermv set_First_Player_params(1);
	set_First_Player_params[0] = PlAtom(plSymbol);

	//invoque setFirstPlayer predicate
	PlQuery	setFirstPlayer("setFirstPlayer2", set_First_Player_params);
	setFirstPlayer.next_solution();
}

//Bum!
int TicTacToePLEngine::plHumanPlay(int square)
{
	//prepare parameters (Square,ReturnedStatus):
	PlTermv human_play_params(2);
	human_play_params[0] = square;

	//invoque humanPlay predicate
	PlQuery	humanPlay("humanPlay", human_play_params);
	humanPlay.next_solution();

	// Read an return output parameter
	return human_play_params[1];
}

int TicTacToePLEngine::plComputerPlay()
{
	//Create parameters (BestMove,ReturnedStatus)
	PlTermv play_params(2);

	//Invoque the play predicate
	PlQuery play("computerPlay", play_params);
	play.next_solution();

	status = play_params[1]; //Status is updated
	//Read and return output parameter:
	return play_params[0]; //Best Move
	
}

string TicTacToePLEngine::getMessage()
{
	return message;
}

int TicTacToePLEngine::getComputerMove()
{
	return plComputerPlay();
}

int TicTacToePLEngine::getStatus()
{
	return status;
}

