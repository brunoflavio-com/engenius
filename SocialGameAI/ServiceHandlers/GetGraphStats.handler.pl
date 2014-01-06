%
% FILE: GetGraphStats.handler.pl
%

%
% Social Game Server: Handler for Graph stats
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
:-http_handler('/getgraphstats', get_graph_stats, []).

%%
% Request Handler:
get_graph_stats(_) :-			
	get_graph_stats_action(Total, Average),
	prolog_to_json(UserGraph, UserGraphJSON),
	reply_json(UserGraphJSON).

%%
% Compute:
get_graph_stats_action(Total, Average) :-
	get_total_friends(Total),
	get_average_connection_strength(Average).

get_total_friends(Total):-
	findall(Name,
		http_session_data(user(Name,_,_,_,_,_,_,_,_)),
		List),
	length(List,Total1),
	Total is Total1-1.
	
get_average_connection_strength(Average):-
	findall(Strength,
		http_session_data(relationship(_,_,_,Strength))
		,List),
	sum_list(List,Sum),
	length(List,Count),
	Average is Sum/Count.