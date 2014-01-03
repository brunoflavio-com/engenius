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


%%
% Compute:
