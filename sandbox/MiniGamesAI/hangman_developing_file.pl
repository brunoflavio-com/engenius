%%%%%%%%%% TESTS %%%%%%%%%%

%hangman(category,word)
%:-dynamic hangman/2.

%hangman(marcaCarros, toyota).
%hangman(marcaCarros, honda).
%hangman(marcaCarros, bmw).
%hangman(marcaCarros, audi).
%hangman(marcaCarros, mercedes).

%assert(hangman(marcaCarros,rover)).

%cenas(L,R):- findall(L,used(L),R).
%get all used characters
	%cenas(R):- findall(U,used(U),R).
%14 ?- compare(>,5,2).
%true.

%15 ?- compare(=,[1,2,3],[1,2,3]).
%true.

%16 ?- compare(>,[1,2,3],[1,2,3]).

%?21 ?- string_to_list(texto,L).
%L = [116, 101, 120, 116, 111].

%find (character,word)
%find(X,Y):- read(X), char_code(X,L), member(L,"texto").
%find(X,Y):- char_code(X,LX), string_to_list(Y,LY), member(LX,LY).

%(condicao1,condicao2,condicao3,((condicao4, condicao5,R is 0);R is 1));R is 2.

%10 ?- string_to_list('abc',LY).
%LY = [97, 98, 99].

%11 ?- string_to_list(abc,LY).
%LY = [97, 98, 99].

%15 ?- string_chars(abc,L).
%L = [a, b, c].

%23 ?- char_code(a,L).
%L = 97.


%12 ?- word(W),string_chars(W,L).
%W = abc,
%L = [a, b, c].

%13 ?- findall(U,used(U),LH), word(W),string_chars(W,L), intersection(LH,L,LR).
%LH = [a, x, b, c],
%W = abc,
%L = LR, LR = [a, b, c].

%14 ?- findall(U,used(U),LH), word(W),string_chars(W,L), intersection(LH,L,LR),compare(=,L,LR), write('YEAH!').
%YEAH!
%LH = [a, x, b, c],
%W = abc,
%L = LR, LR = [a, b, c].


%1 ?- assert(word('abc')).
%true.

%2 ?- play('a',R).
%R = 1.

%3 ?- play('b',R).
%R = 1.

%4 ?- play('c',R).
%R = 1.

%5 ?- chekWin(R).
%WIN!
%R = 0. 

%1 ?- assert(word('abc')).
%true.

%2 ?- play('b',R).
%R = 1.

%3 ?- chekWin(R).
%false.

%4 ?- play('a',R).
%R = 1.

%5 ?- play('c',R).
%R = 1.

%6 ?- chekWin(R).
%WIN!
%R = 0.


%%%%%%%%%% TO USE PREDICATES %%%%%%%%%%

:- dynamic word/1.
:- dynamic used/1.

%already used characters knowledge base example
%used(a).
%used(b).
%used(c).
%used(d).
%used(r).

%starting game cpp - assert(word(W)).
%during game Prolog - assert(used(C)).
%Results: 	0 - Win;
%			1 - word contains character;
%			2 - word does not contains character.
			
%play (Character,Result)			
play(C,R):- not(checkRepeated(C,R)), 			
			assert(used(C)),
			!,
			find(C,R).
			
%checkWin(Character,CheckRepeatedResult)		
checkRepeated(CA,CRR):-	findall(US,used(US),LUS),
						member(CA,LUS),
						CRR is 3,
						write('Repeated').

%find (Character,Result)
find(X,R):-	( word(W),
			string_chars(W,LW),
			member(X,LW),
			((checkWin(R),!); R is 1,!)); R is 2.

%checkWin(CheckWinResult)
checkWin(CWR):-	findall(U,used(U),LH),
				word(W),
				string_chars(W,L),
				intersection(LH,L,LR),			
				same_length(L,LR),
				CWR is 0,
				write('WIN!').
				
teste(R):- R is 3, true.