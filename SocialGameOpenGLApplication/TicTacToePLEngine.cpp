#include "TicTacToePLEngine.h"


TicTacToePLEngine::TicTacToePLEngine(char symbolFirstPlayer)
{
	
	char* argv [] = { "libswipl.dll", "-s", "tictactoe.pl", NULL };

	prolog = new PlEngine(3, argv);
	plSetFirstPlayer(symbolFirstPlayer);
	status = -1;

	message = "Hi, good luck playing Tic Tac Toe!";

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
	PlQuery	setFirstPlayer("setFirstPlayer", set_First_Player_params);
	setFirstPlayer.next_solution();
	
}


void TicTacToePLEngine::plHumanPlay(int square)
{
	//prepare parameters (Square,ReturnedStatus):
	PlTermv human_play_params(2);
	human_play_params[0] = square;

	//invoque humanPlay predicate
	PlQuery	humanPlay("humanPlay", human_play_params);
	humanPlay.next_solution();

	//this->message = "well done!";
	status = human_play_params[1]; //Status is updated
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
	message = "Computer played\n Select square!";
	return plComputerPlay();
}

int TicTacToePLEngine::getStatus()
{
	if (status == 0) message = "DRAW";
	else if (status == 1) message = "YOU WIN";
	else if (status == 2) message = "COMPUTER WIN";
	else message = "playing tic tac toe";
	return status;
}


void TicTacToePLEngine::playTTT(int square)
{
	plHumanPlay(square);
	getStatus();

}

	