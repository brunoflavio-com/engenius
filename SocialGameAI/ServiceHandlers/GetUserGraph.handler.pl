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
get_user_graph(_) :-			
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
			%the lists we'll need:			
			'Users'=UsersJSON,
			'Relationships'=RelationshipsJSON,
			
			%not used:
			'Interests'=[],			
			'RelationshipTags'=[],
		        'HumourStatus'=[]
		      ]
		    ).

%%
% Process users:

get_users(UsersJSON):-
	findall(
	  %output
	  json(
		    [
		      'Email'= Email,
		      'Name'= Name,
		      'Surname'= Surname,
		      'Birthdate'= Birthdate,
		      'HumourStatusId'= HumourStatusID,
		      'InterestsIDs'= Interests,
		      'PhoneNumber'= PhoneNumber,
		      'LinkedInProfile'= LinkedInProfile,
		      'FacebookProfile'= FacebookProfile
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
		  'UserAEmail'=UserA,
		  'UserBEmail'=UserB,
		  'RelationshipTagId'= TagID,
		  'Strength'=Strength
		]
	  ),
	  %search
	  http_session_data(relationship(UserA, UserB, TagID, Strength)),
	  %destination
	  RelationshipsJSON
	).