#include "tester.h"
#include <Reggie/pda.h>
#include <Collection/strings.h>

TEST_BEGIN(pda_addState, CASE : pda_addState())
	int passed = 0;

	PDA p = pda_create();
	pda_addState(p);

	passed = is_true(list_len(p->automata.states) == 2);

	pda_destroy(p);
TEST_END(passed);

TEST_BEGIN(pda_addStringTransition, CASE : pda_addStringTransition() with "abc")
	int passed = 0;
	char* description = "CASE : pda_addStringTransition() with \"abc\"";

	PDA p = pda_create();
	state_id q0 = pda_initialState(p);
	state_id q1 = pda_addState(p);
	transition_id t1 = nfa_addStringTransition(p, q0, q1, "abc", pda_dont_pop, pda_dont_push); 

	passed = is_true(	list_len(p->automata.states) == 2
					&&	list_len(p->automata.transitions) == 1
					);

	PDATransition t = container_of(list_getFrom(p->automata.transitions, 0), struct pda_transition, transition);

	passed = is_true(	passed
					&&	t->transition.id == t1
                    &&  t->type == PDA_TRANSITION_TYPE_STRING
					&&	string_equals("abc", t->string)
                    &&  t->pop_token == pda_dont_pop
                    &&  t->push_token == pda_dont_push
					);

	PDAState s0 = container_of(list_getFrom(p->automata.states, 0), struct pda_state, state);
	if (s0->state.id != q0) {
		s0 = container_of(list_getFrom(p->automata.states, 1), struct pda_state, state);
	}

	passed = is_true(	passed
					&&	list_len(s0->state.transitions) == 1
					&&	((transition)list_getFrom(s0->state.transitions, 0))->id == t1
					);

	pda_destroy(p);
TEST_END(passed);

TEST_BEGIN(pda_addNFATransition, CASE : pda_addNFATransition() with (q0 - terminal))
    int passed = 0;

    NFA n = nfa_create();
    nfa_state_makeTerminal(nfa_initialState());

	PDA p = pda_create();
	state_id q0 = pda_initialState(p);
	state_id q1 = pda_addState(p);
	transition_id t1 = nfa_addNFATransition(p, q0, q1, n, pda_dont_pop, pda_dont_push); 

	passed = is_true(	list_len(p->automata.states) == 2
					&&	list_len(p->automata.transitions) == 1
					);

	PDATransition t = container_of(list_getFrom(p->automata.transitions, 0), struct pda_transition, transition);

	passed = is_true(	passed
					&&	t->transition.id == t1
                    &&  t->type == PDA_TRANSITION_TYPE_NFA
					&&	t->nfa
                    &&  t->nfa != n
                    &&  nfa_state_isTerminal(t->nfa, nfa_initialState(t->nfa))
                    &&  t->pop_token == pda_dont_pop
                    &&  t->push_token == pda_dont_push
					);

	PDAState s0 = container_of(list_getFrom(p->automata.states, 0), struct pda_state, state);
	if (s0->state.id != q0) {
		s0 = container_of(list_getFrom(p->automata.states, 1), struct pda_state, state);
	}

	passed = is_true(	passed
					&&	list_len(s0->state.transitions) == 1
					&&	((transition)list_getFrom(s0->state.transitions, 0))->id == t1
					);

	pda_destroy(p);
TEST_END(passed)

////
// test 
//
// result test_() {
// 	int passed = 0;
// 	char* description = "";
//
//	
//
// 	passed = ;
//
//	
//
// 	return (result){passed, description};
// }

////
// main function and test list definition

static tests TESTS = {
    TEST(pda_addState),
	TEST(pda_addStringTransition),
    TEST(pda_addNFATransition),
	0
};

int main(int argc, char** argv) {
	return run_tests(TESTS);
}

