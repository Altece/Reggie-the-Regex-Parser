Reggie the Regex Parser
=======================

Reggie the Regex Parser (RRP) is a regualr expression parser that will have the ability to identify strings that match the regular expression.

Purpose
-------

To learn about and understand regualr expressions and finite automata.

To write awesome things in the C language.

To become a badass and super-being among mortals.

To create the foundations for a regex parser for possible future use in attempts at creating compilers.

Design
------

Regualr expressions are written forms of a non-deterministic finite automata (NFA), which represents a machine that matches strings of characters for patterns encoded within the machine.

An NFA is a directed graph with one initial node state (known as "q0") and any number of other states. Any number of states within the NFA can be an accepting state that would signify the acceptance of a string when the string encounters its end. Transitions between states are invoked by encountering specified characters. [Learn more about NFAs from Wikipedia](http://en.wikipedia.org/wiki/Nondeterministic_finite_automaton).

This regex parser will take a regualr expression string and create an NFA modeled by that string.

A user can then take the resulting NFA and pass in a string to see if it passes the NFA.

NFAs for Use with Parsing
-------------------------

A strict NFA would not be useful for parsing purposes. If you wanted to tokenize using an NFA, you would need to know how long the string that is accepted by the NFA is, and you would need to be able to deal with anything following the final accept terminal state.

A parsing evaluator needs to be implemented to allow for the length of any accepting substring in an input string, so long as the substring and the input string start together.

NFA Copying
-----------

The recursive structure of an NFA makes cloning and copying less than arbitrary. A template representing a blueprint for the NFA is created, and then an NFA structure is built from the generated template.

The template is a map of state pointers to state representations, and from transition pointers to transition representations.

Public Interface
----------------

The `reggie.h` file reveals the public interface for the regex parser. This file includes function definitions that facilitate the creation, destruction, use for matching, use for parsing, and manipulation of regualr expressions backed by NFAs.

Possible Future Exploations
---------------------------

The use of a modified Non-Deterministic Push-Down Automata (PDA) may be useful for implementing a regular-expression parsing machine that could also be used outside the regex parsing to become a general-purpose parser.

Source Highlights
-----------------

`list.h` is a mean C Linked-List Library featuring a `FOREACH` macro looping construct and more.

`map.h` is a map or dictionary implementation based on the `list.h` library allowing for primative key-value storying of any pointer data values.

`nfa.h` holds the structure of the Non-Deterministic Finite Automata and it's parts.

Compilation
-----------

To compile and run tests, run

	make test

To clean the build files, run

	make clean

To clean the build files and binaries, run

	make real-clean
