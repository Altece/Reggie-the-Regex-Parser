#include "nfa_operations-test.h"
#include "../src/nfa.h"
#include "../src/nfa_eval.h"

////
// set up tests

NFA gen_A_NFA() {
	NFA a = nfa_create();

	State q1 = state_create();
	state_setName(q1, "q1");
	state_makeTerminal(q1);

	state_addTransition(nfa_initialState(a), "a", q1);

	return a;
}

NFA gen_B_NFA() {
	NFA b = nfa_create();

	State q1 = state_create();
	state_setName(q1, "q1");
	state_makeTerminal(q1);

	state_addTransition(nfa_initialState(b), "b", q1);

	return b;
}

NFA gen_C_NFA() {
	NFA c = nfa_create();

	State q1 = state_create();
	state_setName(q1, "q1");
	state_makeTerminal(q1);

	state_addTransition(nfa_initialState(c), "c", q1);

	return c;
}

////
// test NFA nfa_CONCAT(NFA, NFA)

result test_nfa_CONCAT_A_CONCAT_B() {
	int passed = 0;
	char* description = "nfa_CONCAT(NFA, NFA) : ab";

	NFA a = gen_A_NFA();
	NFA b = gen_B_NFA();

	NFA nfa = nfa_CONCAT(a, b);

	passed = is_true(nfa_eval(nfa, "ab"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

////
// test NFA nfa_UNION(NFA, NFA)

result test_nfa_UNION_A_UNION_B() {
	int passed = 0;
	char* description = "nfa_UNION(NFA, NFA) : a|b";

	NFA a = gen_A_NFA();
	NFA b = gen_B_NFA();

	NFA nfa = nfa_UNION(a, b);

	passed = is_true(nfa_eval(nfa, "a")) &&
			 is_true(nfa_eval(nfa, "b")) &&
			 is_false(nfa_eval(nfa, "ab"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

////
// test NFA nfa_KLEENE(NFA)

result test_nfa_KLEENE_A_KLEENE() {
	int passed = 0;
	char* description = "nfa_KLEENE(NFA) : a*";

	NFA a = gen_A_NFA();

	NFA nfa = nfa_KLEENE(a);

	passed = is_true(nfa_eval(nfa, "")) &&
			 is_true(nfa_eval(nfa, "a")) &&
			 is_true(nfa_eval(nfa, "aa")) &&
			 is_true(nfa_eval(nfa, "aaa"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

////
// testing chaining

result test_aUb_CONCAT_c() {
	int passed = 0;(
		char* description = "(a|b)c";

	NFA a = gen_A_NFA();
	NFA b = gen_B_NFA();
	NFA c = gen_C_NFA();

	NFA nfa = nfa_CONCAT(nfa_UNION(a, b), c);

	passed = is_true(nfa_eval(nfa, "ac")) &&
			 is_true(nfa_eval(nfa, "bc")) &&
			 if_false(nfa_eval(nfa, "c"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

result test_aUbUc() {
	int passed = 0;(
		char* description = "(a|b)|c";

	NFA a = gen_A_NFA();
	NFA b = gen_B_NFA();
	NFA c = gen_C_NFA();

	NFA nfa = nfa_UNION(nfa_UNION(a, b), c);

	passed = is_true(nfa_eval(nfa, "a")) &&
			 is_true(nfa_eval(nfa, "b")) &&
			 if_true(nfa_eval(nfa, "c")) &&
			 if_false(nfa_eval(nfa, "ab")) &&
			 if_false(nfa_eval(nfa, "bc")) &&
			 if_false(nfa_eval(nfa, "ac")) &&
			 if_false(nfa_eval(nfa, "ca"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

result test_aUb_KLEENE() {
	int passed = 0;(
		char* description = "(a|b)*";

	NFA a = gen_A_NFA();
	NFA b = gen_B_NFA();

	NFA nfa = nfa_KLEENE(nfa_UNION(a, b));

	passed = is_true(nfa_eval(nfa, "")) &&
			 is_true(nfa_eval(nfa, "a")) &&
			 is_true(nfa_eval(nfa, "aa")) &&
			 is_true(nfa_eval(nfa, "b")) &&
			 is_true(nfa_eval(nfa, "bb")) &&
			 is_true(nfa_eval(nfa, "ab")) &&
			 is_true(nfa_eval(nfa, "ba")) &&
			 is_true(nfa_eval(nfa, "aba"));

	nfa_destroy(nfa);

	return (result){passed, description};
}

////
// main function and test list definition

static tests TESTS = {
	// basic testing
	&test_nfa_CONCAT_A_CONCAT_B,
	&test_nfa_UNION_A_UNION_B,
	&test_nfa_KLEENE_A_KLEENE,

	// testing chaining
	&test_aUb_CONCAT_c,
	&test_aUbUc,
	&test_aUb_KLEENE,

	0
};

int main(int argc, char** argv) {
	run_tests(TESTS);
	return 0;
}