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
:-http_handler('/getcommontagfriends', get_common_tag_friends, []).

%%
% Request Handler:
get_common_tag_friends(Request) :-
	get_common_tag_friends_action(Request,CommonTagFriends),
	prolog_to_json(CommonTagFriends, CommonTagFriendsJSON),
	reply_json(CommonTagFriendsJSON).

%%
% Compute:
get_common_tag_friends_action(Request,CommonTagFriends) :-
	findall([User,Interests],
		user(User, _, _, _, _, Interests, _, _, _),
		UserList),
	get_common_tag_friends_action1(Request,CommonTagFriends,UserList).
	
get_common_tag_friends_action1(_,[],[]).
get_common_tag_friends_action1(Request,[User|CommonTagFriends],[[User,Interests]|T]):-
	checkcommontags(Request,Interests),
	get_common_tag_friends_action1(Request,CommonTagFriends,T).
get_common_tag_friends_action1(Request,CommonTagFriends,[_|T]):-
	get_common_tag_friends_action1(Request,CommonTagFriends,T).
	
checkcommontags([],_).
checkcommontags([H|T],Interests):-
	(member(H,Interests),checkcommontags(T,Interests));(!,fail).
	
	