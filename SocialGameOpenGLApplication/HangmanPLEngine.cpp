#include "HangmanPLEngine.h"

HangmanPLEngine::HangmanPLEngine(int maxRetries, string word)
{
	char* argv[] = { "libswipl.dll", "-s", "hangman.pl", NULL };
	prolog = new PlEngine (3, argv);

	this->maxRetries = maxRetries;
	setWord(word);

	message = "Hi, guess the word!\n Enter the first letter:";
	gameOver = false;
}


HangmanPLEngine::~HangmanPLEngine()
{
	delete prolog;
}

void HangmanPLEngine::play(char attempt)
{
	if (gameOver) return;
	
	int result = plPlay(attempt);

	switch (result) {
	case 1:
		message = "Correct, \"";
		message += attempt;
		message += "\" belongs to this word!\nGuess the next letter:";
		break;
	case 2:
		message = "\"";
		message += attempt;
		message +="\" doesn't belongs to this word, sorry!\nTry again:";
		curRetries++;
		break;
	case 0:
		gameOver = true;
		break;
	}

	if (curRetries >= maxRetries){		
		gameOver = true;
		if (hasWon()) {
			message = "Congratulations, you won!";
		}
		else {
			message = "Game over, better luck next time...";
		}
	}
}

int HangmanPLEngine::plPlay(char attempt)
{
	char plAttempt[2] = { attempt, '\0' };

	//Create paramters (Value, Result)
	PlTermv play_params(2);
	play_params[0] = PlAtom(plAttempt);

	//Invoque the play predicate
	PlQuery play("play", play_params);
	play.next_solution();

	//Read and return output parameter:
	return play_params[1];
}

void HangmanPLEngine::setWord(string word)
{
	//prepare parameters:
	PlTermv set_word_params(1);
	set_word_params[0] = word.c_str();
	
	//invoque set_word predicate
	PlQuery	set_word("set_word", set_word_params);
	set_word.next_solution();
}


bool HangmanPLEngine::isGameOver(bool &winner) 
{
	if (gameOver) winner = hasWon();
	return gameOver;
}

int HangmanPLEngine::noOfRetries()
{
	return curRetries;
}

string HangmanPLEngine::getMessage()
{
	return message;
}

bool HangmanPLEngine::hasWon()
{
	if (!gameOver) return false;
	return curRetries < maxRetries;
}