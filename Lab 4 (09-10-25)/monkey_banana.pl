% Monkey and Banana Problem in Prolog

% Dynamic declarations
:- dynamic(at/2).
:- dynamic(has/1).

% Initial state
at(monkey, door).
at(banana, middle).
at(box, window).
has(nothing).

% Actions

move(monkey, From, To) :-
    at(monkey, From),
    retract(at(monkey, From)),
    assert(at(monkey, To)).

push(box, From, To) :-
    at(monkey, From),
    at(box, From),
    retract(at(box, From)),
    assert(at(box, To)),
    retract(at(monkey, From)),
    assert(at(monkey, To)).

climb_box :-
    at(monkey, Pos),
    at(box, Pos),
    retract(at(monkey, Pos)),
    assert(at(monkey, on_box)).

grasp_banana :-
    at(monkey, on_box),
    at(box, middle),
    at(banana, middle),
    retract(has(nothing)),
    assert(has(banana)).

% Goal
goal_state :-
    has(banana),
    write('✅ Monkey has the banana!'), nl.

% Plan to reach the goal
solve :-
    move(monkey, door, window),
    push(box, window, middle),
    climb_box,
    grasp_banana,
    goal_state.