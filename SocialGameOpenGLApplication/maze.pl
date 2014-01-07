
set_node(L,C):-assertz(node(L,C)).


%In same Column
liga(LineI, ColumnI, LineG, ColumnG):-ColumnI == ColumnG, (Dif is LineI - 1; Dif is LineI + 1), Dif == LineG.
%In same Line
liga(LineI, ColumnI, LineG, ColumnG):-LineI == LineG, (Dif is ColumnI - 1; Dif is ColumnI + 1), Dif == ColumnG.

next(Line, Column, LineG, ColumnG):-node(LineG, ColumnG), liga(Line, Column, LineG, ColumnG).

all_next(Line, Column, L):-findall((LineG, ColumnG),(next(Line, Column, LineG, ColumnG)), L).

path(LineI, ColumnI,LineG, ColumnG, LineS, ColumnS):-path1(LineI, ColumnI, LineG, ColumnG, [(LineI, ColumnI)], [_,(LineS, ColumnS)|_]),!.

path1(LineG, ColumnG, LineG, ColumnG, LPath, LFinal):-reverse(LPath, LFinal).

path1(LineI, ColumnI, LineG, ColumnG, LPath, LFinal):-next(LineI, ColumnI, LineTemp, ColumnTemp), not(member((LineTemp, ColumnTemp), LPath)), path1(LineTemp, ColumnTemp, LineG, ColumnG, [(LineTemp, ColumnTemp)|LPath], LFinal).
