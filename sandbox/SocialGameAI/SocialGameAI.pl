% grafo
% 1 --> 2 --> 3 --> 4
%      |    |
%      |--------> 5
%      |          |
%      \-------------> 6

:-dynamic(conn/2).

path(X,Y,[conn(X,Y)]) :- conn(X,Y).
path(X,Y,[conn(X,Z)|C]) :- conn(X,Z),path(Z,Y,C).

insert(X,Y):-assertz(conn(X,Y)).

insert([]).
insert([Conn|R]):-
	Conn=json([ori=Ori,des=Des]),
	insert(Ori,Des),
	format('Inserted connection: ~w => ~w ~n', [Ori,Des]),
	insert(R).

%%
% Libraries
%%
:- use_module(library(http/thread_httpd)). % servidor http
:- use_module(library(http/http_dispatch)). % execução de pedidos ao servidor.
:- use_module(library(http/http_parameters)). % processamento de parâmetros enviados via métodos GET e POST 
:- use_module(library(http/http_session)). 
:- use_module(library(http/http_json)).
:- use_module(library(http/json)).
:- use_module(library(http/json_convert)).
:- use_module(library(http/http_error)).

%%
% HTTP Server					
%%
server(Port) :-						
        http_server(http_dispatch, [port(Port)]).

%%
% Handlers:
%%		
		
:- http_handler('/parsejson', handle, []).
:- http_handler('/register_lig1', register_lig1, []).
:- http_handler('/register_lig2', register_lig2, []).


%%
% Predicates
%%
:- json_object 
	insert(ori:integer, des:integer) + [type=insert].

handle(Request) :-	
	http_read_json(Request, JSONIn),	
	json_to_prolog(JSONIn, X), 
	format('Content-type: text/plain~n~n'),
	evaluate(X).
	%format('Conns: ~w ~n',[Conns]).
	%prolog_to_json(Conns, JSONOut),
	%reply_json(JSONOut).
	

evaluate(PrologIn) :-
        PrologIn = json([conn=Conns,method=insert]),	
        MethodName = insert,
	format('Method: OK~n'),
        insert(Conns),
	%format('Conns: ~w~n', [Conns]),
	format('done.~n').
 
%register_lig(Request) :-
%    	http_parameters(Request,
%	                JSONIn),
%
%	json_to_prolog(JSONIn, PrologIn),
%
%	%format('L: ~w~n',R),
%    	format('Content-type: text/plain~n~n').
%    	format('json:( ~w )~n',[JSONIn]).
	
register_lig1(Request) :-
    http_parameters(Request,
                    [ ori(Origin, [between(1,10)]),
                      dest(Destination, [between(1,10)])
                    ]),
    http_session_assert(conn(Origin,Destination)),
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

%inicializar o servidor:
:-server(5000).	
