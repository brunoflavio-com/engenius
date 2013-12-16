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
	load_user_graph_action(UserGraph).

%%
% Compute:
load_user_graph_action(UserGraph) :-
        UserGraph = json([relationships=RelationshipsJSON,users=UsersJSON]),       
	format('Loading Graph~n'),
        insert_users(UsersJSON),
        %insert_relationships(RelationshipsJSON),
	format('done.~n').

%%
% Process users:
insert_users([]).
insert_users([UserJSON | T]):-
	insert_user(UserJSON),
	insert_users(T).

insert_user(UserJSON):-
	UserJSON = json([birthdate=Birthdate, emails=Email, facebookprofile=FacebookProfile, humourstatusid=HumourStatusID, interestsids=InterestsJSON, linkedinprofile=LinkedInProfile, name=Name, phonenumber=PhoneNumber, surname=Surname]),    
	assert(user(Email, Name, Surname, Birthdate, PhoneNumber, HumourStatusID, FacebookProfile, LinkedInProfile)).
