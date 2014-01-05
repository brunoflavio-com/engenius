%
% FILE: GetCommonTagFriends.handler.pl
%

%
% Social Game Server: Handler for friends with common tags.
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
:-http_handler('/getfriendswithcommoninterests', get_friends_with_common_interests, []).

%%
% Request Handler:
get_friends_with_common_interests(Request) :-
        http_read_json(Request, JSONIn),
        json_to_prolog(JSONIn, CommonInterests),
	get_friends_with_common_interests_action(CommonInterests,CommonTagFriends),	
	prolog_to_json(CommonTagFriends, CommonTagFriendsJSON),
	reply_json(CommonTagFriendsJSON).

%%
% Compute:
get_friends_with_common_interests_action(CommonInterests,CommonTagFriends) :-
	findall([User,Interests],
		http_session_data(user(User, _, _, _, _, Interests, _, _, _)),
		UserList),
	get_friends_with_common_interests_action1(CommonInterests,CommonTagFriends,UserList).
	
get_friends_with_common_interests_action1(_,[],[]).
get_friends_with_common_interests_action1(CommonInterests,[User|CommonTagFriends],[[User,Interests]|T]):-
	check_common_interests(CommonInterests,Interests),
	get_friends_with_common_interests_action1(CommonInterests,CommonTagFriends,T).
get_friends_with_common_interests_action1(CommonInterests,CommonTagFriends,[_|T]):-
	get_friends_with_common_interests_action1(CommonInterests,CommonTagFriends,T).
	
check_common_interests([],_).
check_common_interests([H|T],Interests):-
	(member(H,Interests),check_common_interests(T,Interests));(!,fail).
	
	