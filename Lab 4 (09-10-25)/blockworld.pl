% -------- Block World Problem --------

:- dynamic(on/2).
:- dynamic(clear/1).

% Initial configuration
on(a, table).
on(b, table).
on(c, a).

clear(b).
clear(c).

% move(X, From, To)
move(X, From, To) :-
    clear(X),
    clear(To),
    on(X, From),
    X \= To,
    retract(on(X, From)),
    assert(on(X, To)),
    retract(clear(To)),
    assert(clear(From)),
    write('Moved '), write(X), write(' from '), write(From),
    write(' to '), write(To), nl.

% To show current world state
show_state :-
    write('--- Current Configuration ---'), nl,
    listing(on),
    listing(clear).

