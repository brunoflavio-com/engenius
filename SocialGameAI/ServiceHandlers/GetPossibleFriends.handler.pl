%
% FILE: GetPossibleFriends.handler.pl
%

%
% Social Game Server: Handler for sugesting new friend(s)
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
:-http_handler('/getpossiblefriends', get_possible_friends, []).

%%
% Request Handler:
get_possible_friends(Request) :-
	http_parameters(Request,
                    [ 
					useremail(UserEmail, [])
					]),
	get_possible_friends_action(UserEmail, SugestedFriends),
	prolog_to_json(SugestedFriends, SugestedFriendsJSON),
	reply_json(SugestedFriendsJSON).

%%
% Compute:
get_possible_friends_action(UserEmail, SugestedFriends):-





