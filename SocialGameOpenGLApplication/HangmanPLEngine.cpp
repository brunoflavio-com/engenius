#include "HangmanPLEngine.h"

HangmanPLEngine::HangmanPLEngine(int maxRetries, string word)
{
	char* argv[] = { "libswipl.dll", "-s", "hangman.pl", NULL };
	prolog = new PlEngine (3, argv);

	this->maxRetries = maxRetries;
	setWord(word);

	message = "Hi, guess the word!\n Enter the first letter:";
	curRetries = 0;
	gameOver = false;
}

HangmanPLEngine::~HangmanPLEngine()
{
	delete prolog;
}

//play guess and retrive information
void HangmanPLEngine::play(char attempt)
{
	if (gameOver) return;
	
	int result = plPlay(attempt);

	switch (result) {
	case 1:
		message = "Correct, \"";
		message += attempt;
		message += "\" belongs to this word!\nGuess the next letter:";
		message += "\n\nCurrent retries: " + std::to_string(curRetries);
		break;
	case 2:
		message = "\"";
		message += attempt;
		message +="\" doesn't belongs to this word, sorry!\nTry again:";
		curRetries++;
		message += "\n\nCurrent retries: " + std::to_string(curRetries);
		break;
	case 3:
		message = "\"";
		message += attempt;
		message += "\" repeated letter, sorry!\nTry again:";
		curRetries++;
		message += "\n\nCurrent retries: " + std::to_string(curRetries);
		break;

	}

	isGameOver();

}

//from prolog predicate find, and assert attempt
//1 - word contains character;
//2 - word does not contains character.
//3 - character repeated
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

//prolog assert word
void HangmanPLEngine::setWord(string word)
{
	this->word = word;
	//prepare parameters:
	PlTermv set_word_params(1);
	set_word_params[0] = word.c_str();
	
	//invoque set_word predicate
	PlQuery	set_word("set_word", set_word_params);
	set_word.next_solution();
}

//Verify if there is a winner (Win - 0; otherwise -1)
int HangmanPLEngine::plWinner()
{
	//Create parameters (Result)
	PlTermv winner_params(1);

	//Invoque the winner predicate
	PlQuery w("win", winner_params);
	w.next_solution();

	//Read and return output parameter:
	return winner_params[0];
}

//Verify gameover
bool HangmanPLEngine::isGameOver() 
{
	int status = plWinner();
	if (curRetries > maxRetries){
		gameOver = true;
		winner = false;
		message = "Game over, Can't retry anymore...";
		message += "\n\n\Solution: " + this->word;
		return true;
	}
	if (curRetries < maxRetries && status == 0){
		gameOver = true;
		winner = true;
		message = "Congratulations, you won!\n\n";
		message += std::to_string(PRIZE - (curRetries * 100));
		message += " Points! ";
		return true;
	}
	if (curRetries == maxRetries && status == -1){
		gameOver = true;
		winner = false;
		message = "Game over, better luck next time...";
		message += "\n\n\Solution: " + this->word;
		return true;
	}
	else
		return false;
}

//number of tries
int HangmanPLEngine::noOfRetries()
{
	return curRetries;
}

string HangmanPLEngine::getMessage()
{
	return message;
}

//Player win?
bool HangmanPLEngine::isWinner()
{
	return winner;
}


