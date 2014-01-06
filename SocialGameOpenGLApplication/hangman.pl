
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

%set_word (Word)
set_word(Word):- 
			retractall(word(_)),
			retractall(used(_)), 
			assert(word(Word)).

%find (Character,Result)
find(X,R):-	( word(W),
			string_chars(W,LW),
			member(X,LW),
			((checkWin(R),!); R is 1,!)); R is 2.


%play (Character,Result)
%Results: 	0 - Win;
%			1 - word contains character;
%			2 - word does not contains character.
%			3 - character repeated			
play(C,R):- findall(US,used(US),LUS),
			member(C,LUS),
			R is 3,
			!.			
				
%play (Character,Result)			
play(C,R):- 
			assert(used(C)),
			!,
			find(C,R).

%checkRepeated(Character,CheckRepeatedResult)		
checkRepeated(CA,CRR):-
			findall(US,used(US),LUS),
			member(CA,LUS),
			CRR is 3,
			write('Repeated').

%checkWin(CheckWinResult)
checkWin(CWR):-
			findall(U,used(U),LH),
			word(W),
			string_chars(W,L),
			intersection(LH,L,LR),			
			same_length(L,LR),
			CWR is 0.

