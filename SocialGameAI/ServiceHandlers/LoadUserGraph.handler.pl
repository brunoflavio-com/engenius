%
% FILE: LoadUserGraph.handler.pl
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
:-http_handler('/loadusergraph', load_user_graph, []).

%%
% Request Handler:
load_user_graph(Request) :-	
	http_read_json(Request, JSONIn),	
	json_to_prolog(JSONIn, UserGraph), 
	format('Content-type: text/plain~n~n'),	
	%format('UserGraph: ~w~n', [UserGraph]),	
	load_user_graph_action(UserGraph).

%%
% Compute:
load_user_graph_action(UserGraph) :-
        UserGraph = json(
		      [
			%not used:
		        'HumourStatus'=_,
		        %not used:
			'Interests'=_,
			
			%the lists we'll need:
			'Relationships'=RelationshipsJSON,
			'Users'=UsersJSON
		      ]
		    ),  
		    
	format('Loading Graph~n'),
        insert_users(UsersJSON),
        insert_relationships(RelationshipsJSON),
	format('done.~n').

%%
% Process users:
insert_users([]).
insert_users([UserJSON | T]):-
	insert_user(UserJSON),
	insert_users(T).

insert_user(UserJSON):-
	UserJSON = json(
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
	http_session_assert(user(Email, Name, Surname, Birthdate, PhoneNumber, Interests, HumourStatusID, FacebookProfile, LinkedInProfile)),
	format('*Created user ~w.~n', [Email]).

%%
% Process relationships:
insert_relationships([]).
insert_relationships([RelationshipJSON | T]):-
	insert_relationship(RelationshipJSON),
	insert_relationships(T).
	
insert_relationship(RelationshipJSON):-
	RelationshipJSON = json(
			      [
				'RelationshipTagId'= TagID,
				'Strength'=Strength,
				'UserAEmail'=UserA,
				'UserBEmail'=UserB
			      ]
			  ),
	http_session_assert(relationship(UserA, UserB, TagID, Strength)),
	format('*Created relationship between ~w and ~w.~n', [UserA, UserB]).
	