%
% FILE: graph.pl
%

%
% Social Game OpenGL Application: Methods for finding paths in the graph.
%

%%MODEL:

%Relationship fact: relationship(emailA, emailB, Strength)
:-dynamic(relationship/3).

%%ASSERTION METHODS:
insert(UserA, UserB, Strength):-
	assert(relationship(UserA, UserB, Strength)).

cleargraph:-retractall(relationship(_,_,_)).

%%SHORTEST
find_shortest_path(UserAEmail, UserBEmail, Path):-
  find_shortest_path1([[UserAEmail]], UserBEmail , InvertedPath),
  reverse(InvertedPath, Path).
 
%find_shortest_path1([CurrentPath | PendingPaths], Destination, Path)
find_shortest_path1(
    [ [Destination|Visited] |_],
    Destination,
    [Destination|Visited]
    ).

find_shortest_path1(
    [ [CurrentUser | VisitedUsers] | OtherPaths ],
    Destination,
    Path
    ):-	find_next_users_shortest(CurrentUser, VisitedUsers, L),
	append(OtherPaths, L, NewPaths),
	find_shortest_path1(NewPaths, Destination, Path).

find_next_users_shortest(CurrentUser, VisitedUsers, L) :-
    findall(	[ ProxUser, CurrentUser | VisitedUsers ],
		(	(
			  relationship(CurrentUser, ProxUser, _)
			  ;
			  relationship(ProxUser, CurrentUser, _)
			),
			not(member(ProxUser, VisitedUsers))
		),
		L
	  ).

%%STRONGEST
find_strongest_path(UserAEmail, UserBEmail, Path):-
  find_strongest_path1([(0 , [UserAEmail])], UserBEmail , InvertedPath),
  reverse(InvertedPath, Path).

%find_strongest_path1([CurrentPath | PendingPaths], Destination, Path)
find_strongest_path1(
    [(_, [Destination|Visited]) |_],
    Destination,
    [Destination|Visited]
    ).

find_strongest_path1(
    [(CurrentAverage, [CurrentUser | VisitedUsers]) | OtherPaths ],
    Destination,
    Path
    ):-	find_next_users_strongest(CurrentAverage,[CurrentUser | VisitedUsers], L),
	append(OtherPaths, L, NP),
	sort(NP, NP2),
	reverse(NP2, NewPaths),
	find_strongest_path1(NewPaths, Destination, Path).

find_next_users_strongest(CurrentAverage, [CurrentUser | VisitedUsers] , L) :-
    findall(	( Average, [ ProxUser, CurrentUser | VisitedUsers ]),
		(	(
			  relationship(CurrentUser, ProxUser, Strength)
			  ;
			  relationship(ProxUser, CurrentUser, Strength)
			),
			not(member(ProxUser, VisitedUsers)),
			length([CurrentUser|VisitedUsers],NoUsers),
			Average is (((CurrentAverage * NoUsers) + Strength) / (NoUsers + 1))
		),
		L
	  ).
  