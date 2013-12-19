// ConsoleTicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SWI-cpp.h>
#include <iostream>

using namespace std;



int main()
{
	char* argv[] = { "libswipl.dll", "-s", "tictactoe.pl", NULL };
	PlEngine e(3, argv);
	PlTermv av(1);
	//predicado
	PlQuery	q("possible_moves", av);
	while (q.next_solution())
	{
		cout << (char*) av[0] << endl;
	}
	cin.get();
	return 1;
}

