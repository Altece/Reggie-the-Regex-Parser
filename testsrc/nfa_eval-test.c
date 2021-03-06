#include "tester.h"
#include <Reggie/nfa_eval.h>
#include <Reggie/nfa.h>

////
// set up an NFA for the regex aba

NFA aba_nfa() {
	NFA n = nfa_create();
	state_id q0 = nfa_initialState(n);
	state_id q1 = nfa_addState(n);
	state_id q2 = nfa_addState(n);
	state_id q3 = nfa_addState(n);
	nfa_state_makeTerminal(n, q3);

	nfa_addTransition(n, q0, q1, "a");
	nfa_addTransition(n, q1, q2, "b");
	nfa_addTransition(n, q2, q3, "a");

	return n;
}

////
// test int state_eval(State, char*)

result test_state_eval_Empty_PASSING() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"\" passing terminal CASE";

	NFA n = nfa_create();
	nfa_state_makeTerminal(n, nfa_initialState(n));

	passed = is_true(nfa_eval(n, ""));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_s_Failing() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"s\" failing terminal CASE";

	NFA n = nfa_create();
	nfa_state_makeTerminal(n, nfa_initialState(n));

	passed = is_false(nfa_eval(n, "s"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_EmptyString_FailingNonTerminal() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"\" failing non-terminal CASE";

	NFA n = nfa_create();

	passed = is_false(nfa_eval(n, ""));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_a_PassingWithTransition() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"a\" passing with transition CASE";

	NFA n = nfa_create();
	state_id s = nfa_addState(n);
	nfa_state_makeTerminal(n, s);
	nfa_addTransition(n, nfa_initialState(n), s, "a");

	passed = is_true(nfa_eval(n, "a"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_aa_FailingWithTransition() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"aa\" failing with transition CASE";

	NFA n = nfa_create();
	state_id s = nfa_addState(n);
	nfa_state_makeTerminal(n, s);
	nfa_addTransition(n, nfa_initialState(n), s, "a");

	passed = is_false(nfa_eval(n, "aa"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_aa_PassingWithEpsilonTransition() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"aa\" passing with epsilon transition CASE";

	NFA n = nfa_create();
	state_id s0 = nfa_initialState(n);
	state_id s1 = nfa_addState(n);
	state_id s2 = nfa_addState(n);
	state_id s3 = nfa_addState(n);
	nfa_state_makeTerminal(n, s3);
	nfa_addTransition(n, s0, s1, "a");
	nfa_addTransition(n, s1, s2, "");
	nfa_addTransition(n, s2, s3, "a");

	passed = is_true(nfa_eval(n, "aa"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_a_PassingWithFirstTransition() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"a\" passing with second transition CASE";

	NFA n = nfa_create();
	state_id s0 = nfa_initialState(n);
	state_id s1 = nfa_addState(n);
	nfa_state_makeTerminal(n, s1);
	nfa_addTransition(n, s0, s1, "a");
	nfa_addTransition(n, s0, s1, "b");

	passed = is_true(nfa_eval(n, "a"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_a_PassingWithSecondTransition() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"a\" passing with second transition CASE";

	NFA n = nfa_create();
	state_id s0 = nfa_initialState(n);
	state_id s1 = nfa_addState(n);
	nfa_state_makeTerminal(n, s1);
	nfa_addTransition(n, s0, s1, "b");
	nfa_addTransition(n, s0, s1, "a");

	passed = is_true(nfa_eval(n, "a"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_state_eval_aa_FailingWithSecondTransition() {
	int passed = 0;
	char* description = "state_eval(State, char*) : \"aa\" failing with second transition CASE";

	NFA n = nfa_create();
	state_id s0 = nfa_initialState(n);
	state_id s1 = nfa_addState(n);
	nfa_state_makeTerminal(n, s1);
	nfa_addTransition(n, s0, s1, "b");
	nfa_addTransition(n, s0, s1, "a");

	passed = is_false(nfa_eval(n, "aa"));

	nfa_destroy(n);

	return (result){passed, description};
}

////
// test int nfa_eval(NFA, char*)

result test_nfa_eval_ABA_PASSING() {
	int passed = 0;
	char* description = "nfa_eval(NFA, char*) : aba passing CASE";

	NFA n = aba_nfa();

	passed = is_true(nfa_eval(n, "aba"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_nfa_eval_ABA_PASSINGWithEpsilons() {
	int passed = 0;
	char* description = "nfa_eval(NFA, char*) : aba passing with epsilons CASE";

	NFA n = nfa_create();
	state_id states[8];
	states[0] = nfa_initialState(n);
	for (int i = 1; i < 8; i++) {
		states[i] = nfa_addState(n);
	}

	nfa_addTransition(n, states[0], states[1], "");
	nfa_addTransition(n, states[1], states[2], "");
	nfa_addTransition(n, states[2], states[3], "");
	nfa_addTransition(n, states[3], states[4], "a");
	nfa_addTransition(n, states[4], states[5], "b");
	nfa_addTransition(n, states[5], states[6], "a");
	nfa_state_makeTerminal(n, states[6]);

	passed = is_true(nfa_eval(n, "aba"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_nfa_eval_aUb_PASSINGWithEpsilons() {
	int passed = 0;
	char* description = "nfa_eval(NFA, char*) : a|b passing with epsilons CASE";

	NFA n = nfa_create();
	state_id q0 = nfa_initialState(n);
	state_id q1 = nfa_addState(n);
	state_id q2 = nfa_addState(n);
	state_id q3 = nfa_addState(n);
	state_id q4 = nfa_addState(n);

	nfa_addTransition(n, q0, q1, "");
	nfa_addTransition(n, q0, q2, "");
	nfa_addTransition(n, q1, q3, "a");
	nfa_addTransition(n, q2, q4, "b");
	nfa_state_makeTerminal(n, q3);
	nfa_state_makeTerminal(n, q4);

	passed = is_true(nfa_eval(n, "a")) && is_true(nfa_eval(n, "b"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_nfa_eval_ABA_Failing() {
	int passed = 0;
	char* description = "nfa_eval(NFA, char*) : aba failing CASE";

	NFA n = aba_nfa();

	passed = is_false(nfa_eval(n, "aaa"));

	nfa_destroy(n);

	return (result){passed, description};
}

result test_nfa_eval_complicated() {
	int passed = 0;
	char *description = "nfa_eval(NFA, char*) : (a|b)c(d|e) *COMPLICATED* CASE";

	NFA n = nfa_create();
	state_id s0 = nfa_initialState(n);
	state_id s1 = nfa_addState(n);
	state_id s2 = nfa_addState(n);
	state_id s3 = nfa_addState(n);
	state_id s4 = nfa_addState(n);
	state_id s5 = nfa_addState(n);
	state_id s6 = nfa_addState(n);
	state_id s7 = nfa_addState(n);
	nfa_addTransition(n, s0, s1, "");
	nfa_addTransition(n, s0, s2, "");
	nfa_addTransition(n, s1, s3, "a");
	nfa_addTransition(n, s2, s3, "b");
	nfa_addTransition(n, s3, s4, "c");
	nfa_addTransition(n, s4, s5, "");
	nfa_addTransition(n, s4, s6, "");
	nfa_addTransition(n, s5, s7, "d");
	nfa_addTransition(n, s6, s7, "e");
	nfa_state_makeTerminal(n, s7);

	passed = is_false(nfa_eval(n, "a")) &&
			is_false(nfa_eval(n, "b")) &&
			is_false(nfa_eval(n, "c")) &&
			is_false(nfa_eval(n, "d")) &&
			is_false(nfa_eval(n, "e")) &&
			is_false(nfa_eval(n, "ab")) &&
			is_false(nfa_eval(n, "bc")) &&
			is_false(nfa_eval(n, "cd")) &&
			is_false(nfa_eval(n, "de")) &&
			is_false(nfa_eval(n, "abcde")) &&
			is_true(nfa_eval(n, "acd")) &&
			is_true(nfa_eval(n, "bce")) &&
			is_true(nfa_eval(n, "ace")) &&
			is_true(nfa_eval(n, "bcd"));

	return (result){passed, description};
}

////
// main function and test list definition

static tests TESTS = {
	// test state_eval() (also tests transition_eval() by proxy)
	&test_state_eval_Empty_PASSING,
	&test_state_eval_s_Failing,
	&test_state_eval_EmptyString_FailingNonTerminal,
	&test_state_eval_a_PassingWithTransition,
	&test_state_eval_aa_FailingWithTransition,
	&test_state_eval_aa_PassingWithEpsilonTransition,
	&test_nfa_eval_aUb_PASSINGWithEpsilons,
	&test_state_eval_a_PassingWithSecondTransition,
	&test_state_eval_aa_FailingWithSecondTransition,

	// test nfa_eval()
	&test_nfa_eval_ABA_PASSING,
	&test_nfa_eval_ABA_PASSINGWithEpsilons,
	&test_nfa_eval_ABA_Failing,

	&test_nfa_eval_complicated,
	
	0
};

int main(int argc, char** argv) {
	return run_tests(TESTS);
}

