#include "nfa_parsing_eval-test.h"
#include "../src/nfa.h"
#include "../src/nfa_parsing_eval.h"

////
// set up an NFA for the regex aba

NFA aba_nfa() {
	NFA nfa = nfa_create();

	State q1 = state_create();
	state_setName(q1, "q1");

	State q2 = state_create();
	state_setName(q2, "q2");

	State q3 = state_create();
	state_setName(q3, "q3");
	state_makeTerminal(q3);

	state_addTransition(nfa_initialState(nfa), "a", q1);
	state_addTransition(q1, "b", q2);
	state_addTransition(q2, "a", q3);

	return nfa;
}

////
// test int state_parsing_eval(State, char*)

result test_state_parsing_eval_Empty_PASSING() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"\" passing terminal CASE";

	State s = state_create();
	state_makeTerminal(s);

	passed = is_nonfalse(state_parsing_eval(s, ""));

	state_destroy(s);

	return (result){passed, description};
}

result test_state_parsing_eval_s_PassingOnEmptyStringTerminal() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"s\" passing on empty string terminal CASE";

	State s = state_create();
	state_makeTerminal(s);

	passed = is_nonfalse(state_parsing_eval(s, "s"));

	state_destroy(s);

	return (result){passed, description};
}

result test_state_parsing_eval_EmptyString_FailingNonTerminal() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"\" failing non-terminal CASE";

	State s = state_create();

	passed = is_false(state_parsing_eval(s, ""));

	state_destroy(s);

	return (result){passed, description};
}

result test_state_parsing_eval_a_PassingWithTransition() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"a\" passing with transition CASE";

	State q2 = state_create();
	state_setName(q2, "q2");
	State q3 = state_create();
	state_setName(q3, "q3");
	state_makeTerminal(q3);

	state_addTransition(q2, "a", q3);

	passed = is_nonfalse(state_parsing_eval(q2, "a"));

	state_destroy(q2);
	state_destroy(q3);

	return (result){passed, description};
}

result test_state_parsing_eval_aa_PassingLenght1WithTransition() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"aa\" passing length 1 with transition CASE";

	State q2 = state_create();
	state_setName(q2, "q2");
	State q3 = state_create();
	state_setName(q3, "q3");
	state_makeTerminal(q3);

	state_addTransition(q2, "a", q3);

	passed = is_nonfalse(state_parsing_eval(q2, "aa"));

	state_destroy(q2);
	state_destroy(q3);

	return (result){passed, description};
}

result test_state_parsing_eval_a_PassingWithSecondTransition() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"a\" passing with second transition CASE";

	State q2 = state_create();
	state_setName(q2, "q2");
	State q3 = state_create();
	state_setName(q3, "q3");
	state_makeTerminal(q3);

	state_addTransition(q2, "b", q3);
	state_addTransition(q2, "a", q3);

	passed = is_nonfalse(state_parsing_eval(q2, "a"));

	state_destroy(q2);
	state_destroy(q3);

	return (result){passed, description};
}

result test_state_parsing_eval_aa_PassingWithEpsilonTransition() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"aa\" passing with epsilon transition CASE";

	State q1 = state_create();
	state_setName(q1, "q1");
	State q2 = state_create();
	state_setName(q2, "q2");
	State q3 = state_create();
	state_setName(q3, "q3");
	State q4 = state_create();
	state_setName(q4, "q4");
	state_makeTerminal(q4);

	state_addTransition(q1, "a", q2);
	state_addTransition(q2, "", q3);
	state_addTransition(q3, "a", q4);

	passed = is_nonfalse(state_parsing_eval(q1, "aa"));

	state_destroy(q1);
	state_destroy(q2);
	state_destroy(q3);
	state_destroy(q4);

	return (result){passed, description};
}

result test_state_parsing_eval_aa_FailingWithSecondTransition() {
	int passed = 0;
	char* description = "state_parsing_eval(State, char*) : \"aa\" failing with second transition CASE";

	State q2 = state_create();
	state_setName(q2, "q2");
	State q3 = state_create();
	state_setName(q3, "q3");
	state_makeTerminal(q3);

	state_addTransition(q2, "b", q3);
	state_addTransition(q2, "c", q3);

	passed = is_false(state_parsing_eval(q2, "aa"));

	state_destroy(q2);
	state_destroy(q3);

	return (result){passed, description};
}

////
// test int nfa_parsing_eval(NFA, char*)

result test_nfa_parsing_eval_ABA_PASSING() {
	int passed = 0;
	char* description = "nfa_parsing_eval(NFA, char*) : aba passing CASE";

	NFA nfa = aba_nfa();

	passed = is_nonfalse(nfa_parsing_eval(nfa, "aba"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

result test_nfa_parsing_eval_ABAAAA_PassingLength3() {
	int passed = 0;
	char* description = "nfa_parsing_eval(NFA, char*) : abaaaa passing length 3 CASE";

	NFA nfa = aba_nfa();

	passed = is_equal(nfa_parsing_eval(nfa, "abaaaa"), 3);

	nfa_destroy(nfa);

	return (result){passed, description};
}

result test_nfa_parsing_eval_ABA_Failing() {
	int passed = 0;
	char* description = "nfa_parsing_eval(NFA, char*) : aba failing CASE";

	NFA nfa = aba_nfa();

	passed = is_false(nfa_parsing_eval(nfa, "aaa"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

////
// main function and test list definition

static tests TESTS = {
	// test state_parsing_eval() (also tests transition_eval() by proxy)
	&test_state_parsing_eval_Empty_PASSING,
	&test_state_parsing_eval_s_PassingOnEmptyStringTerminal,
	&test_state_parsing_eval_EmptyString_FailingNonTerminal,
	&test_state_parsing_eval_a_PassingWithTransition,
	&test_state_parsing_eval_aa_PassingLenght1WithTransition,
	&test_state_parsing_eval_a_PassingWithSecondTransition,
	&test_state_parsing_eval_aa_FailingWithSecondTransition,

	// test nfa_parsing_eval()
	&test_nfa_parsing_eval_ABA_PASSING,
	&test_nfa_parsing_eval_ABAAAA_PassingLength3,
	&test_nfa_parsing_eval_ABA_Failing,
	
	0
};

int main(int argc, char** argv) {
	run_tests(TESTS);
	return 0;
}