%%%%%%%%%% TO USE PREDICATES %%%%%%%%%%

:- dynamic edge/2.

%graph representation knowledge base example
edge(a,b).
edge(a,c).
edge(a,d).
edge(b,e).
edge(b,f).
edge(c,f).
edge(c,g).
edge(d,g).
edge(d,h).
edge(d,i).
edge(e,j).
edge(f,a).
edge(f,j).
edge(f,k).
edge(g,f).
edge(g,o).
edge(g,h).
edge(h,d).
edge(h,l).
edge(i,l).
edge(j,m).
edge(j,n).
edge(k,n).
edge(k,p).
edge(l,p).

%starting game cpp, various - assert(edge(a,b)).

hint(Orig,Dest,L) :- hint(Orig,Dest,[Orig],[_,L|_]),!.
hint(Dest,Dest,LPath,LFinal):-reverse(LPath,LFinal).
hint(Orig,Dest,LPath,LFinal) :-
							edge(Orig,X),
							not(member(X,LPath)),
							hint(X,Dest,[X|LPath],LFinal).