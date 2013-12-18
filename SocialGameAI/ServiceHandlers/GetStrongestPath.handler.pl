%
% FILE: GetStrongestPath.handler.pl
%

%
% Social Game Server: Handler for strongest path retrieval
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
:-http_handler('/getstrongestpath', get_strongest_path, []).

%%
% Request Handler:
get_strongest_path(Request) :-
	http_parameters(Request,
                    [ origin(Origin, []),
                      destination(Destination, [])
                    ]),
	get_strongest_path_action(Origin, Destination, Path),
	prolog_to_json(Path, PathJSON),
	reply_json(PathJSON).

%%
% Compute:
get_strongest_path_action(Origin, Destination, StrongestPath) :-
	find_strongest_path(Origin, Destination, StrongestPath).