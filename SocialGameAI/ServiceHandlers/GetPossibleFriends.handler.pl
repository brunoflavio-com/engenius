%
% FILE: GetPossibleFriends.handler.pl
%

%
% Social Game Server: Handler for sugesting new friends
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
		[ useremail(UserEmail, [])
		]),
	get_possible_friends_action(UserEmail, SugestedFriends),
	prolog_to_json(SugestedFriends, SugestedFriendsJSON),
	reply_json(SugestedFriendsJSON).

%%
% Compute:
get_possible_friends_action(UserEmail, SugestedFriends):-
	findall((Common,UserB),
		(http_session_data(user(UserB,_,_,_,_,_,_,_,_)),
			UserB\=UserEmail,
			not(http_session_data(relationship(UserEmail,UserB,_,_))),
			not(http_session_data(relationship(UserB,UserEmail,_,_))),
			get_common_interests(UserEmail,UserB, Common)),
		List),
	sort(List, List1),
	reverse(List1,List2),
	findall(User,
		member((_,User),List2),
		SugestedFriends).

get_common_interests(UserA,UserB, Common):-
	http_session_data(user(UserA,_,_,_,_,InterestsA,_,_,_)),
	http_session_data(user(UserB,_,_,_,_,InterestsB,_,_,_)),
	get_common_interests_action(InterestsA, InterestsB, Common),!.
	
get_common_interests_action([], _, 0).
get_common_interests_action([H|T], InterestsB, Common):-
	member(H,InterestsB),
	get_common_interests_action(T,InterestsB,Common1),
	Common is Common1+1.
get_common_interests_action([_|T], InterestsB, Common):-
	get_common_interests_action(T,InterestsB,Common).





