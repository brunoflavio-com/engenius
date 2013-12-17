%%% Jogo do Galo

:- dynamic board/1. % inform the interpreter that the board may change during execution
:- retractall(board(_)). % clean the discovered facts out of the database
:- assert(board([_A,_B,_C,_D,_E,_F,_G,_H,_I])). % a Prolog list to represent the board 

%% predicate show_board - to display board 
show_board([A,B,C,D,E,F,G,H,I]) :- 
	write([A,B,C]),nl,
	write([D,E,F]),nl,
	write([G,H,I]),nl,nl.
	
%% predicate to mark a free spot on the board
mark(Player, [X|_],1,1) :- var(X), X=Player.
mark(Player, [_,X|_],1,2) :- var(X), X=Player.
mark(Player, [_,_,X|_],1,3) :- var(X), X=Player.
mark(Player, [_,_,_,X|_],2,1) :- var(X), X=Player.
mark(Player, [_,_,_,_,X|_],2,2) :- var(X), X=Player.
mark(Player, [_,_,_,_,_,X|_],2,3) :- var(X), X=Player.
mark(Player, [_,_,_,_,_,_,X|_],3,1) :- var(X), X=Player.
mark(Player, [_,_,_,_,_,_,_,X|_],3,2) :- var(X), X=Player.
mark(Player, [_,_,_,_,_,_,_,_,X|_],3,3) :- var(X), X=Player.

win(Player):-board([Player,Player,Player,_,_,_,_,_,_]).
win(Player):-board([_,_,_,Player,Player,Player,_,_,_]).
win(Player):-board([_,_,_,_,_,_,Player,Player,Player]).
win(Player):-board([Player,_,_,Player,_,_,Player,_,_]).
win(Player):-board([_,Player,_,_,Player,_,_,Player,_]).
win(Player):-board([_,_,Player,_,_,Player,_,_,Player]).
win(Player):-board([Player,_,_,_,Player,_,_,_,Player]).
win(Player):-board([_,_,Player,_,Player,_,Player,_,_]).


%% predicate to insert a move on the board
insert_move(Player,X,Y) :- 
   retract(board(Board)), 
   mark(Player,Board,X,Y),
   assert(board(Board)),
   show_board(Board).
   
%% predicate to find all possible moves


possible_moves(Moves):- findall((X,Y),(board(Board),mark(_,Board,X,Y)),Moves).