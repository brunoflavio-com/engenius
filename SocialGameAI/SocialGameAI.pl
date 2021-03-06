%
% FILE: SocialGameAI.pl
%

%
% Social Game AI Module:
%

:-format('##Starting the SocialGameAI Module.~n').

:-format('###Loading configurations.~n'),
    consult('SocialGameAI.conf.pl').

:-format('###Loading the model.~n'),
    consult('Model.pl').

:-format('###Loading the search methods.~n'),
    consult('Search.methods.pl').
    
%%TODO: load graph handling predicates
    
:-format('###Starting the webservice.~n'),
    consult('Server.pl').