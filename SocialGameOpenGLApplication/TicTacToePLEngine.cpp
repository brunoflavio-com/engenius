#include "TicTacToePLEngine.h"


TicTacToePLEngine::TicTacToePLEngine(char symbolFirstPlayer)
{
	
	char * argv [] = { "libswipl.dll", "-s", "tictactoe.pl", NULL };

	prolog = new PlEngine(3, argv);
	plSetFirstPlayer(symbolFirstPlayer);

	message = "Hi, good luck playing Tic Tac Toe!\nYou Start!";

}

TicTacToePLEngine::~TicTacToePLEngine()
{
	delete prolog;
}

void TicTacToePLEngine::plSetFirstPlayer(char symbol)
{
	//prepare parameters:
	PlTermv setFirstPlayer_params(1);
	setFirstPlayer_params[0] = symbol;

	//invoque setFirstPlayer predicate
	PlQuery	setFirstPlayer("setFirstPlayer", setFirstPlayer_params);
	setFirstPlayer.next_solution();
}

int TicTacToePLEngine::plHumanPlay(int square)
{

	//prepare parameters (Square,ReturnedStatus):
	PlTermv human_play_params(1);
	human_play_params[0] = square;

	//invoque humanPlay predicate
	PlQuery	humanPlay("humanPlay", human_play_params);
	humanPlay.next_solution();

	// Read an return output parameter
	return human_play_params[1];
}

int TicTacToePLEngine::plComputerPlay()
{
	//Create parameters (ReturnedStatus)
	PlTermv play_params(1);

	//Invoque the play predicate
	PlQuery play("computerPlay", play_params);
	play.next_solution();

	
	//Read and return output parameter:
	return play_params[1];
}

int TicTacToePLEngine::plStatusGame()
{
	//Create paramters (Result)
	PlTermv status_params(1);

	//Invoque the play predicate
	PlQuery status("gameStatus", status_params);
	status.next_solution();

	//Read and return output parameter:
	// status 2 -> computer wins
	// status 1 -> human wins
	// status 0 -> draw
	// status -1 -> playing
	return status_params[1];
}


string TicTacToePLEngine::getMessage()
{
	return message;
}



void TicTacToePLEngine::play(int square)
{

	//int status = plHumanPlay( square);

}