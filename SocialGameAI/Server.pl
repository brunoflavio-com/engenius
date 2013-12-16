%
% FILE: SocialGameAI.conf.pl
%

%
% Social Game Server:
%

%%
% Libraries
:- use_module(library(http/thread_httpd)). % servidor http
:- use_module(library(http/http_dispatch)). % execução de pedidos ao servidor.
:- use_module(library(http/http_parameters)). % processamento de parâmetros enviados via métodos GET e POST 
:- use_module(library(http/http_session)).
:- use_module(library(http/http_error)).


%%
% predicate that starts webserver.
server(Port) :- http_server(http_dispatch, [port(Port)]).


%%
% Load list of files:
consult_list([], Count):-Count is 0.
consult_list([File|T], Count):-
  %load current file:
  format('####Loading [~w]~n', [File]),
  consult(File),
  %recursive call to ourselves:
  consult_list(T, C),
  %update the number of files loaded:
  Count is C + 1.
  

%Server SCRIPT:

%%
% Load all Handlers in the folder ServiceHandlers that end with ".handler.pl"
:- expand_file_name('ServiceHandlers/*.handler.pl', Handlers),
   consult_list(Handlers, Count),
   format('####Finished loading ~w file.~n', [Count]).
   

%%
% Ready to start the webserver:
% See SocialGameAI.conf.pl for the port used:
:-webservice_port(Port),
    format('###Starting the webservice on port ~w.~n',[Port]),
    server(Port).