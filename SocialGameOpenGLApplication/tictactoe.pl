%% TIC TAC TOE GAME

%% inform the interpreter that the board may change during execution
:- dynamic game/2. 
%% clean the discovered facts out of the database
:- retractall(game(_,_)). 

cleartictactoe:-retractall(game(_,_)).

%% set player that will start the game and initialize the board
%% to represent the game:
% game([Board,Player]) 
% Board - a Prolog list to represent the Board (Squares 1-9) 
% Player - next player to play (x or o)
setFirstPlayer(Player):- assert(game([_,_,_,_,_,_,_,_,_],Player)). 


%% mark a move on board(Square:1-9)
%mark(Player,Board,NewBoard,Position)
mark(Player, [_,B,C,D,E,F,G,H,I],[X,B,C,D,E,F,G,H,I],1):- X = Player.
mark(Player, [A,_,C,D,E,F,G,H,I],[A,X,C,D,E,F,G,H,I],2):- X = Player.
mark(Player, [A,B,_,D,E,F,G,H,I],[A,B,X,D,E,F,G,H,I],3):- X = Player.
mark(Player, [A,B,C,_,E,F,G,H,I],[A,B,C,X,E,F,G,H,I],4):- X = Player.
mark(Player, [A,B,C,D,_,F,G,H,I],[A,B,C,D,X,F,G,H,I],5):- X = Player.
mark(Player, [A,B,C,D,E,_,G,H,I],[A,B,C,D,E,X,G,H,I],6):- X = Player.
mark(Player, [A,B,C,D,E,F,_,H,I],[A,B,C,D,E,F,X,H,I],7):- X = Player.
mark(Player, [A,B,C,D,E,F,G,_,I],[A,B,C,D,E,F,G,X,I],8):- X = Player.
mark(Player, [A,B,C,D,E,F,G,H,_],[A,B,C,D,E,F,G,H,X],9):- X = Player.

%% verify if a Player wins
win([A,B,C,_,_,_,_,_,_],Player) :- A==Player, B==Player, C==Player.
win([_,_,_,A,B,C,_,_,_],Player) :- A==Player, B==Player, C==Player.
win([_,_,_,_,_,_,A,B,C],Player) :- A==Player, B==Player, C==Player.
win([A,_,_,B,_,_,C,_,_],Player) :- A==Player, B==Player, C==Player.
win([_,A,_,_,B,_,_,C,_],Player) :- A==Player, B==Player, C==Player.
win([_,_,A,_,_,B,_,_,C],Player) :- A==Player, B==Player, C==Player.
win([A,_,_,_,B,_,_,_,C],Player) :- A==Player, B==Player, C==Player.
win([_,_,A,_,B,_,C,_,_],Player) :- A==Player, B==Player, C==Player.

%% change player
% nextPlayer(Player, NextPlayer)
nextPlayer(x, o).
nextPlayer(o, x).

%% showBoard - to display board 
showBoard([A,B,C,D,E,F,G,H,I]) :- 
	write([A,B,C]),nl,
	write([D,E,F]),nl,
	write([G,H,I]),nl,nl.

%% insert a move on the board
insertMove(Player,Square) :- game(Board,_),
   filledSquares(Board,Filled),
   \+member(Square,Filled),
   retract(game(Board,_)),
   mark(Player,Board,NewBoard,Square),
   nextPlayer(Player,NextPlayer),
   assert(game(NewBoard,NextPlayer)).
   
%% find all possible moves, if there is none fails
availableSquares(Board,Available):- \+ win(Board,'x'), \+ win(Board,'o'),
findall(X,(mark(Player,_,Board,X),var(Player)),Available),Available \= [].
   
%% find moves in board
filledSquares(Board,Filled):- findall(X,(mark(Player,_,Board,X),nonvar(Player)),Filled).

%% find moves from x in board
xMovesInBoard(Board,XMoves):- findall(X,(mark(Player,_,Board,X),Player==x),XMoves).

%% find moves from o in board
oMovesInBoard(Board,OMoves):- findall(X,(mark(Player,_,Board,X),Player==o),OMoves).

%% verify winner
winner(Board,W):- win(Board,x), W=x,!.
winner(Board,W):- win(Board,o), W=o,!.


%%% Minimax
%% the player playing x is always trying to maximize the utility of the board position
%% the player playing o is always trying to minimize the utility of the board position


%% values "board" states
value(Board,V) :- win(Board,x),V = 1,!.
value(Board,V) :- win(Board,o),V = (-1),!.
value(Board,V) :- V = 0.

maximazing('o').       
minimazing('x').        
	
%%% minimax(Board,Player,Move,Value)
% Move is the best move and Value is the value of that move, the best value from the point 
% of view of the player

minimax(Board,Player,Move,Value):-
	availableSquares(Board,PM),!,
	best(Board,Player,PM,Move,Value).	
	
% if there are no more available moves, minimax value is the value of board
minimax(Board,_,_,Value):-
	value(Board,Value).
	
	
% The best is chosen from the point of view of the Player: 
% X will try to maximize Value and O will try to minimize it.
	
%only one possible move
best(Board,Player,[X],Square,Value):-
	mark(Player,Board,B1,X),
	nextPlayer(Player,NextPlayer),!,
	minimax(B1,NextPlayer,_,Value),
	Square=X,!.
	
best(Board,Player,[X|T],Square,BestValue):- 
	mark(Player,Board,B2,X), % apply the first move X to the board
	nextPlayer(Player,NextPlayer),!,
	minimax(B2,NextPlayer,_,Value), % recursively search for the utility value of that move
	best(Board,Player,T,Move,BestValue), % determine the best move of the remaining moves
	better(Player,X,Value,Move,BestValue,Square,BestValue).
	

% find the best one for Player (x - max, o - min).
% better(Player, Move1, Value1, Move2, Val2, BestMove, BestValue) 
	
better(Player,Move1,Value1,_,Value2,BestMove,BestValue) :-
	maximazing(Player),                     % if the player is maximizing
	Value1 >= Value2,                       % then greater is better.
	BestMove = Move1,						% best move is Move1
	BestValue = Value1,!.					% best value is Value1
	
better(Player,_,_,Move2,Value2,BestMove,BestValue):-
	maximazing(Player),
	BestMove=Move2,BestValue=Value2.


better(Player,Move1,Value1,Move2,Value2,BestMove,BestValue) :-
    minimazing(Player),                     % if the player is minimizing,
	Value1 =< Value2,                        % less is better.
	BestMove = Move1,
	BestValue = Value2,!.

%better(Player,X,Value1,Move2,BestValue2,S,BestValue). % choose the better of the two moves 
better(Player,_,_,Move2,Value2,BestMove,BestValue) :-
	minimazing(Player),                       % if moves have equal value 
	BestMove = Move2,
	BestValue = Value2.	
	
	
	
	

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%     SWI-PROLOG & C++
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

humanPlay(Square,Status):-
	game(Board,o),
	insertMove('o',Square),
	gameStatus(Status).


computerPlay(Square,Status):- 
	game(Board,x),
	minimax(Board,'x',Square,V),
	insertMove('x',Square),
	gameStatus(Status).
	%availableSquares(Board,[_,H|_]),
	%insertMove('x',H),
	%Square=H,gameStatus(Status).

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
