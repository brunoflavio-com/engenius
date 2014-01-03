#include "TicTacToePLEngine.h"


TicTacToePLEngine::TicTacToePLEngine(char symbol)
{
	
	char * argv [] = { "libswipl.dll", "-s", "tictactoe.pl", NULL };

	prolog = new PlEngine(3, argv);
	setFirstPlayer(symbol);

	message = "Hi, good luck playing Tic Tac Toe!";
	gameOver = false;
}

TicTacToePLEngine::~TicTacToePLEngine()
{
	delete prolog;
}

void TicTacToePLEngine::setFirstPlayer(char symbol)
{
	//prepare parameters:
	PlTermv setFirstPlayer_params(1);
	setFirstPlayer_params[0] = symbol;

	//invoque setFirstPlayer predicate
	PlQuery	setFirstPlayer("setFirstPlayer", setFirstPlayer_params);
	setFirstPlayer.next_solution();
}

void TicTacToePLEngine::humanPlay(int square)
{
	//Set Move in Board[]
	setMove(square,HUMAN);

	//prepare parameters:
	PlTermv human_play_params(1);
	human_play_params[0] = square;

	//invoque humanPlay predicate
	PlQuery	humanPlay("humanPlay", human_play_params);
	humanPlay.next_solution();
}

void TicTacToePLEngine::computerPlay()
{
	//Create paramters (Result)
	PlTermv play_params(1);

	//Invoque the play predicate
	PlQuery play("computerPlay", play_params);
	play.next_solution();

	//Set Move in Board
	setMove(play_params[1], COMPUTER);

	//Read and return output parameter:
	//return play_params[1];
}

int TicTacToePLEngine::statusGame()
{
	//Create paramters (Result)
	PlTermv status_params(1);

	//Invoque the play predicate
	PlQuery status("statusGame", status_params);
	status.next_solution();

	//Read and return output parameter:
	// status 2 -> computer wins
	// status 1 -> human wins
	// status 0 -> draw
	// status -1 -> playing
	return status_params[1];
}

bool TicTacToePLEngine::isGameOver()
{
	if (statusGame() >= 0) 
	{
		this->gameOver = true;
		this->winner = statusGame();
		return true;
	}
	else return false;
}

string TicTacToePLEngine::getMessage()
{
	return message;
}

void TicTacToePLEngine::setMove(int square, char player){
	board[square] = player;
}

void TicTacToePLEngine::playTTT()
{
	int computerMove;
	setFirstPlayer(HUMAN);

	while (statusGame() < 0)
	{
		//humanPlay(SQ);
		//computerPlay();

	}


}