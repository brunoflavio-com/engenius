%   +-----+
%   |     |
%   |     O
%   |    -|-
%   |    / \
%   |
% -----

:- dynamic word/1.
:- dynamic used/1.

clearhangman:-retractall(word(_)), retractall(used(_)).

%already used characters knowledge base example
%used(a).
%used(b).
%used(c).
%used(d).
%used(r).

%starting game cpp - assert(word(W)).
%during game Prolog - assert(used(C)).

%set_word (Word)
set_word(Word):- 
			retractall(word(_)),
			retractall(used(_)), 
			assert(word(Word)).
			
%list with letters already used			
usedLetters(UsedLetters):- findall(US,used(US),UsedLetters).

%find (Character,Result)
%Results: 	
%			1 - word contains character;
%			2 - word does not contains character.
%			3 - character repeated
find(X,R):-	usedLetters(L),
			member(X,L),
			R is 3,!.
			
find(X,R):-	word(W), %word 
			string_chars(W,LW), %LW list with all the letters of the word
			\+member(X,LW),	%if char X is not a element of word
			R is 2,!. % Result is 2
			
find(X,R):-	word(W), %word 
			string_chars(W,LW), %LW list with all the letters of the word
			member(X,LW),	%if char X is element of word
			R is 1,!.			

%checkWin true or false
checkWin:-
			usedLetters(LH), %LH  list with all the letters used by player
			word(W),
			string_chars(W,L),%L list with all the letters of the word
			subset(L,LH).
	
% True if all elements of L belong to LH as well	
subset([X],L):- member(X,L).
subset([H|T],List) :-
    member(H,List),
    subset(T,List).

	
% check winner (Win - 0; otherwise -1)
win(W):- checkWin, W is 0,!.
win(W):- W is -1.

% %play (Character,Result)
play(C,R):- find(C,R), assert(used(C)).