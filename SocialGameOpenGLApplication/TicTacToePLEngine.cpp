#include "TicTacToePLEngine.h"
#include "PrologEngine.h"


TicTacToePLEngine::TicTacToePLEngine(char symbolFirstPlayer)
{
	prolog = this->prolog = PrologEngine::getInstance().getEngine();
	clear();

	plSetFirstPlayer(symbolFirstPlayer);
	status = -1;

	message = "\nGood luck!\n";
	message += "\nYou start.\n\n";
	message += "\nInsert position, select[1 - 9]";
	//message += "\n__1__|__2__|__3__";
	//message += "\n__4__|__5__|__6__";
	//message += "\n  7  |  8  |  9  ";
}

TicTacToePLEngine::~TicTacToePLEngine()
{
	clear();
}


void TicTacToePLEngine::clear() {

	PlQuery	plClear("cleartictactoe", NULL);
	plClear.next_solution();

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
	message = "Hi, you're playing Tic Tac Toe\n";
	
}

int TicTacToePLEngine::plHumanPlay(int square)
{
	//prepare parameters (Square,ReturnedStatus):
	PlTermv human_play_params(2);
	human_play_params[0] = square;

	//invoque humanPlay predicate
	PlQuery	humanPlay("humanPlay", human_play_params);
	humanPlay.next_solution();

	return human_play_params[1]; //Status 
}

int TicTacToePLEngine::plComputerPlay()
{
	//Create parameters (BestMove,ReturnedStatus)
	PlTermv play_params(2);

	//Invoque the play predicate
	PlQuery play("computerPlay", play_params);
	play.next_solution();

	//status = play_params[1]; //Status is updated
	//Read and return output parameter:
	return play_params[0]; //Best Move
	
}

string TicTacToePLEngine::getMessage()
{
	return message;
}

int TicTacToePLEngine::getComputerMove()
{
	message = "Select square";
	return plComputerPlay();
}

int TicTacToePLEngine::getStatus()
{
	if (status == 3) message = "Nobody won, better luck next time...";
	else if (status == 1) message = "Congratulations, you won!\n Points: 200! ";
	else if (status == 2) message = "Computer won, better luck next time...";
	else message = "playing tic tac toe";
	return status;
}

void TicTacToePLEngine::playTTT(int square)
{
	status= plHumanPlay(square);
	getStatus();

}

	