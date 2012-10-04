#ifndef NFA_H
#define NFA_H

#include "list.h"

// a transition to a state
typedef struct transition {
	char* transition_string; // a string to transition through when encountered
	struct state* source; // the source state for the transition
	struct state* destination; // the destination state for the transition
} *Transition;

// a state in an nfa
typedef struct state {
	int isTerminalState; // 1 if the state is terminal, 0 otherwise
	char* name; // the name of the state
	list transitions; // a list of transitions that originate from this state
} *State;

// a non-deterministic finite automata
typedef struct nfa {
	struct state* initialState; // the initial state for the nfa
	list states; // a list of states that exist within the nfa
} *NFA;

// create a new nfa object
NFA nfa_create();

// destroy an nfa object and all states within
// use this instead of free
void nfa_destroy(NFA nfa);

// create a new state object
State state_create();

// give a name to a state
// you free the name string if dynamically allcoated
void state_setName(State s, char* name);

// get a state as being a terminal state
void state_makeTerminal(State s);

// destroy a state and all transitions from it
// use this instead of free
void state_destroy(State s);

// add a transition from one state to another through the transition string
void state_addTransition(State s, char* transition_string, State dest);

#endif