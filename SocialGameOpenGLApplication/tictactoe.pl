%%%%
%%% TIC TAC TOE
%%%%

%% inform the interpreter that the board may change during execution
:- dynamic game/2. 
%% clean the discovered facts out of the database
:- retractall(game(_,_)). 

%% predicate to set player that will start the game and initialize the board
%% to represent the game:
% game([Board,Player]) 
% Board - a Prolog list to represent the Board (Squares 1-9) 
% Player - next player to play (x or o)
setFirstPlayer(Player):- assert(game([_,_,_,_,_,_,_,_,_],Player)). 


%% predicate to mark a move (Square:1-9)
mark(Player, [X,_,_,_,_,_,_,_,_],1):- X = Player.
mark(Player, [_,X,_,_,_,_,_,_,_],2):- X = Player.
mark(Player, [_,_,X,_,_,_,_,_,_],3):- X = Player.
mark(Player, [_,_,_,X,_,_,_,_,_],4):- X = Player.
mark(Player, [_,_,_,_,X,_,_,_,_],5):- X = Player.
mark(Player, [_,_,_,_,_,X,_,_,_],6):- X = Player.
mark(Player, [_,_,_,_,_,_,X,_,_],7):- X = Player.
mark(Player, [_,_,_,_,_,_,_,X,_],8):- X = Player.
mark(Player, [_,_,_,_,_,_,_,_,X],9):- X = Player.

%% predicate to verify if a Player wins
win([A,B,C,_,_,_,_,_,_],Player) :- A==Player, B==Player, C==Player.
win([_,_,_,A,B,C,_,_,_],Player) :- A==Player, B==Player, C==Player.
win([_,_,_,_,_,_,A,B,C],Player) :- A==Player, B==Player, C==Player.
win([A,_,_,B,_,_,C,_,_],Player) :- A==Player, B==Player, C==Player.
win([_,A,_,_,B,_,_,C,_],Player) :- A==Player, B==Player, C==Player.
win([_,_,A,_,_,B,_,_,C],Player) :- A==Player, B==Player, C==Player.
win([A,_,_,_,B,_,_,_,C],Player) :- A==Player, B==Player, C==Player.
win([_,_,A,_,B,_,C,_,_],Player) :- A==Player, B==Player, C==Player.

%% predicate  to change player
% nextPlayer(Player, NextPlayer)
nextPlayer(x, o).
nextPlayer(o, x).

%% predicate showBoard - to display board 
showBoard([A,B,C,D,E,F,G,H,I]) :- 
	write([A,B,C]),nl,
	write([D,E,F]),nl,
	write([G,H,I]),nl,nl.

%% predicate to insert a move on the board
insertMove(Player,Square) :- game(Board,_),
   filledSquares(Board,Filled),
   \+member(Square,Filled),
   retract(game(Board,_)),
   mark(Player,Board,Square),
   nextPlayer(Player,NextPlayer),
   assert(game(Board,NextPlayer)).
   
%% predicate to find all possible moves, if there is none fails
availableSquares(Board,Available):- findall(X,(mark(Player,Board,X),var(Player)),Available),Available \= [].
   
%% predicate to find moves in board
filledSquares(Board,Filled):- findall(X,(mark(Player,Board,X),nonvar(Player)),Filled).

%% predicate to find moves from x in board
xMovesInBoard(Board,XMoves):- findall(X,(mark(Player,Board,X),Player==x),XMoves).

%% predicate to find moves from o in board
oMovesInBoard(Board,OMoves):- findall(X,(mark(Player,Board,X),Player==o),OMoves).

%% verify winner
winner(Board,W):- win(Board,x), W=x,!.
winner(Board,W):- win(Board,o), W=o,!.

%% predicate value "board" states
value(Board,V) :- win(Board,x),V = 1,!.
value(Board,V) :- win(Board,o),V = (-1),!.
value(Board,V) :- V = 0.

% the player playing x is always trying to maximize the utility of the board position
% the player playing o is always trying to minimize the utility of the board position
maximizing('x').       
minimizing('o').        
	
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Minimax
% computer is always X, user is O
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

minimax(Board,Player,Move,Value):-
	availableSquares(Board,PM),!,
	best(Board,Player,PM,Move,Value).	
	
% if there are no more available moves,  the minimax value is 
% the eval value of the given board
minimax(Board,Player,Move,Value):-
	value(Board,Value).
	
	
%only one possible move
best(Board,Player,[X],S,Value):-
	mark(Player,Board,X),
	nextPlayer(Player,NextPlayer),!,
	minimax(Board,NextPlayer,_Slast,Value),
	S=X,!.
	
best(Board,Player,[X|T],S,BestValue):-
	mark(Player,Board,X), % apply the first move (in the list) to the board
	nextPlayer(Player,NextPlayer),!,
	minimax(Board,NextPlayer,_S,Value1), % recursively search for the utility value of that move
	best(Board,Player,T,Move2,BestValue2), % determine the best move of the remaining moves
	better(Player,X,Value1,Move2,BestValue2,S,BestValue). % choose the better of the two moves 
	
better(Player,X,Value1,Z,Value2,S,Value) :-
	Value1 == Value2,                            %%% if moves have equal value value,
	S = Z,
	Value = Value2,!.	
	
better(Player,X,Value1,Z,Value2,S,Value) :-
	maximazing(Player),                     %%% if the player is maximizing
	Value1 > Value2,                           %%% then greater is better.
	S = X,
	Value = Value1,!.


better(Nivel,Move,X,Value1,Z,Value2,S,Value) :-
    minimazing(Player),                     %%% if the player is minimizing,
	Value1 < Value2,                            %%% then lesser is better.
	S = X,
	Value = Value1,!.
	

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     MAIN PROGRAM
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

humanPlay(Square,Status):-
	game(Board,o),
	insertMove('o',Square),
	gameStatus(Status).


computerPlay(Square,Status):- 
	game(Board,x),
	availableSquares(Board,[_,H|_]),
	insertMove('x',H),
	Square=H,gameStatus(Status).

%Playing	
gameStatus(Status):-
	game(Board,_),
	\+winner(Board,_),
	Status is -1.
	
%Draw	
gameStatus(Status):-
	game(Board,_),
	\+availableSquares(Board,_),
	\+winner(Board,_),
	Status is 0.

%Computer Wins	
gameStatus(Status):-
	game(Board,_),
	winner(Board,W),
	W=='x', 
	Status is 2.

%Human Wins
gameStatus(Status):-
	game(Board,_),
	winner(Board,W),
	W=='o',
	Status is 1.

%NextPlayer
nextPlayer(Player):-game(_,Player).	
