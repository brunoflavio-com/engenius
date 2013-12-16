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


%%%%%%%%%% TO USE PREDICATES %%%%%%%%%%

:- dynamic word/1.
:- dynamic used/1.

%already used characters knowledge base example
used(a).
used(b).
used(c).
used(d).
used(r).

%starting game cpp - assert(word(W)).
%during game Prolog - assert(used(C)).

find(X,Y,R):- ( char_code(X,LX), string_to_list(Y,LY), member(LX,LY), ((findall(U,used(U),R), compare(=,LY,R), R is 0 ); R is 1)); R is 2.

play(C,R):- not(used(C)),
			assert(used(C)),
			!,
			find(C,W,R).