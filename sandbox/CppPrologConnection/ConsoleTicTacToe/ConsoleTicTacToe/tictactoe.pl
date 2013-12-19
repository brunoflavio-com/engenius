%%% Jogo do Galo

:- dynamic board/1. % inform the interpreter that the board may change during execution
:- retractall(board(_)). % clean the discovered facts out of the database
:- assert(board([_,_,_,_,_,_,_,_,_])). % a Prolog list to represent the board 

% valid users
valid_player(x).
valid_player(o).

% predicate to mark a move (X,Y)
mark_position(Player, [X,_,_,_,_,_,_,_,_],1,1):- X = Player.
mark_position(Player, [_,X,_,_,_,_,_,_,_],1,2):- X = Player.
mark_position(Player, [_,_,X,_,_,_,_,_,_],1,3):- X = Player.
mark_position(Player, [_,_,_,X,_,_,_,_,_],2,1):- X = Player.
mark_position(Player, [_,_,_,_,X,_,_,_,_],2,2):- X = Player.
mark_position(Player, [_,_,_,_,_,X,_,_,_],2,3):- X = Player.
mark_position(Player, [_,_,_,_,_,_,X,_,_],3,1):- X = Player.
mark_position(Player, [_,_,_,_,_,_,_,X,_],3,2):- X = Player.
mark_position(Player, [_,_,_,_,_,_,_,_,X],3,3):- X = Player.

% predicate to verify if a Player wins
win(Player) :- board([A,B,C,_,_,_,_,_,_]),A==Player, B==Player, C==Player.
win(Player) :- board([_,_,_,A,B,C,_,_,_]),A==Player, B==Player, C==Player.
win(Player) :- board([_,_,_,_,_,_,A,B,C]),A==Player, B==Player, C==Player.
win(Player) :- board([A,_,_,B,_,_,C,_,_]),A==Player, B==Player, C==Player.
win(Player) :- board([_,A,_,_,B,_,_,C,_]),A==Player, B==Player, C==Player.
win(Player) :- board([_,_,A,_,_,B,_,_,C]),A==Player, B==Player, C==Player.
win(Player) :- board([A,_,_,_,B,_,_,_,C]),A==Player, B==Player, C==Player.
win(Player) :- board([_,_,A,_,B,_,C,_,_]),A==Player, B==Player, C==Player.


%% predicate show_board - to display board 
show_board([A,B,C,D,E,F,G,H,I]) :- 
	write([A,B,C]),nl,
	write([D,E,F]),nl,
	write([G,H,I]),nl,nl.

%% predicate to insert a move on the board
insert_move(Player,X,Y) :- 
   valid_player(Player),
   board_moves(Moves),
   \+member((X,Y),Moves),
   retract(board(Board)),
   mark_position(Player,Board,X,Y),
   assert(board(Board)),
   show_board(Board).
   
%% predicate to find all possible moves
possible_moves(PMoves):- findall((X,Y),(board(Board),mark_position(Player,Board,X,Y),var(Player)),PMoves).

%% predicate to find moves in board
board_moves(BMoves):- findall((X,Y),(board(Board),mark_position(Player,Board,X,Y),nonvar(Player)),BMoves).

%% predicate to find moves from x in board
x_moves(XMoves):- findall((X,Y),(board(Board),mark_position(Player,Board,X,Y),Player==x),XMoves).

%% predicate to find moves from o in board
o_moves(OMoves):- findall((X,Y),(board(Board),mark_position(Player,Board,X,Y),Player==o),OMoves).
