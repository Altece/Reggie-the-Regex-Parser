#ifndef REGEX_TOKENIZER_NFA_H
#define REGEX_TOKENIZER_NFA_H

#include "nfa.h"

NFA token_nfa_leftParen();

NFA token_nfa_rightParen();

NFA token_nfa_leftSquare();

NFA token_nfa_rightSquare();

NFA token_nfa_pipe();

NFA token_nfa_asterisk();

NFA token_nfa_plus();

NFA token_nfa_escapedChar();

/////////////////////////////////
/// classifiers for char classes
/////////////////////////////////

NFA token_nfa_lowercase();

NFA token_nfa_uppercase();

NFA token_nfa_letter();

NFA token_nfa_digit();

NFA token_nfa_whitespace();

#endif
