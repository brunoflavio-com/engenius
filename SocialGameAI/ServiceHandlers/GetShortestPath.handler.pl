%
% FILE: GetShortestPath.handler.pl
%

%
% Social Game Server: Handler for shortest path retrieval
%

%%
%Libraries:
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/http_parameters)).
:- use_module(library(http/http_session)). 
:- use_module(library(http/http_json)).
:- use_module(library(http/json)).
:- use_module(library(http/json_convert)).
:- use_module(library(http/http_error)).


%%
% Register this handler on the server:
:-http_handler('/getshortestpath', get_shortest_path, []).

%%
% Request Handler:
get_shortest_path(Request) :-
	http_parameters(Request,
                    [ origin(Origin, []),
                      destination(Destination, [])
                    ]),
	get_shortest_path_action(Origin, Destination, Path),
	prolog_to_json(Path, PathJSON),
	reply_json(PathJSON).

%%
% Compute:
get_shortest_path_action(Origin, Destination, ShortestPath) :-
	find_shortest_path(Origin, Destination, ShortestPath).