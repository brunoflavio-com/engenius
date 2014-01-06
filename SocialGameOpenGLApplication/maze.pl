hint(Orig, Dest, L) :- hint(Orig, Dest, [Orig], [_,L|_]),!.
hint(Dest, Dest, LPath, LFinal) :- reverse(LPath, LFinal).
hint(Orig, Dest, LPath, LFinal) :- edge(Orig, X), not(member(X, LPath)), hint(X, Dest, [X|LPath], LFinal).