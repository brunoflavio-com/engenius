%
% FILE: GetUserGraph.handler.pl
%

%
% Social Game Server: Handler for create graph requests.
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
:-http_handler('/getusergraph', get_user_graph, []).

%%
% Request Handler:
get_user_graph(Request) :-			
	get_user_graph_action(UserGraph),
	prolog_to_json(UserGraph, UserGraphJSON),
	reply_json(UserGraphJSON).

%%
% Compute:
get_user_graph_action(UserGraph) :-

	get_users(UsersJSON),
        get_relationships(RelationshipsJSON),        
        
        UserGraph = json(
		      [
			'Relationships'=RelationshipsJSON,
			'Users'=UsersJSON
		      ]
		    ).

%%
% Process users:

get_users(UsersJSON):-
	findall(
	  %output
	  json(
		    [
		      'Birthdate'= Birthdate,
		      'Email'= Email,
		      'FacebookProfile'= FacebookProfile,
		      'HumourStatusId'= HumourStatusID,
		      'InterestsIDs'= Interests,
		      'LinkedInProfile'= LinkedInProfile,
		      'Name'= Name,
		      'PhoneNumber'= PhoneNumber,
		      'Surname'= Surname
		    ]
	  ),
	  %search
	  http_session_data(user(Email, Name, Surname, Birthdate, PhoneNumber, Interests, HumourStatusID, FacebookProfile, LinkedInProfile)),
	  %destination
	  UsersJSON
	).

%%
% Process relationships:
get_relationships(RelationshipsJSON):-
	findall(
	  %output
	  json(
		[
		  'RelationshipTagId'= TagID,
		  'Strength'=Strength,
		  'UserAEmail'=UserA,
		  'UserBEmail'=UserB
		]
	  ),
	  %search
	  http_session_data(relationship(UserA, UserB, TagID, Strength)),
	  %destination
	  RelationshipsJSON
	).