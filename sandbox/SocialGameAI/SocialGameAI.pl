% grafo
% 1 --> 2 --> 3 --> 4
%      |    |
%      |--------> 5
%      |          |
%      \-------------> 6

:-dynamic(conn/2).
conn(1,2).
conn(2,3).
conn(3,4).
conn(3,5).
conn(2,5).
conn(5,6).
conn(2,6).

path(X,Y,[conn(X,Y)]) :- conn(X,Y).
path(X,Y,[conn(X,Z)|C]) :- conn(X,Z),path(Z,Y,C).

insert(X,Y):-assertz(conn(X,Y)).

%%
% Libraries
:- use_module(library(http/thread_httpd)). % servidor http
:- use_module(library(http/http_dispatch)). % execução de pedidos ao servidor.
:- use_module(library(http/http_parameters)). % processamento de parâmetros enviados via métodos GET e POST 
:- use_module(library(http/http_session)). 

% HTTP Server					
server(Port) :-						
        http_server(http_dispatch, [port(Port)]).

%%
% Handlers:
%%		
		
:- http_handler('/register_lig', register_lig, []).
:- http_handler('/register_lig1', register_lig1, []).
:- http_handler('/register_lig2', register_lig2, []).


%%
% Predicates
%%
register_lig(Request) :-
    http_parameters(Request,
                    [ ori(Origin, [between(1,10)]),
                      dest(Destination, [between(1,10)])
                    ]),
    insert(Origin, Destination),
	%format('L: ~w~n',R),
    format('Content-type: text/plain~n~n'),
    format('conn(~w,~w)~n',[Origin,Destination]).
	
register_lig1(Request) :-
    http_parameters(Request,
                    [ ori(Origin, [between(1,10)]),
                      dest(Destination, [between(1,10)])
                    ]),
    http_session_assert(conn(Origin,Destination)),
	%format('L: ~w~n',R),
    format('Content-type: text/plain~n~n'),
    format('conn(~w,~w)~n',[Origin,Destination]).
	
register_lig2(Request) :-
    http_parameters(Request,
                    [ %ori(Origin, [list( integer )]),
					  ori(Origin, [list( integer )]),
                      dest(Destination, [list(integer) ])
                    ]),
    http_session_assert(conn(Origin,Destination)),
	create_fact(Origin,Destination),	
    format('Content-type: text/plain~n~n'),
    format('conn(~w,~w)~n',[Origin,Destination]).

create_fact([],[]).	
create_fact([A|TA], [B|TB]):-
	assertz(conn(A,B)),
	create_fact(TA,TB).
	