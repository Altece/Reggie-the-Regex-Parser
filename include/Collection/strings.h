#ifndef REGGIE_STRINGS_H
#define REGGIE_STRINGS_H

// a collection of string-rlated functions
// because why not implement everything for fun?

// if any string function encounters a NULL pointer, it returns -1

// get the length of the string
int string_length(char* str);

// are the two strings equivalent?
// return 1 if equivalent, 0 otherwise
int string_equals(char* s1, char* s2);

// find if string little is a substring of string big
// return 1 if little is a substring, 0 otherwise.
// this only works if the substring starts with the 
// first cahracter of the superstring.
int string_substring(char* big, char* little);

// copy the null-terminated string into a newly allocated string
// the resulting string must be freed
char* string_copy(char* str);

// copy a substring of the given null-terminated string
// the resulting allocated string is at most the length provided
// the resulting string must be freed
char* string_copy_substring(char *str, int length);

// copy the input strings into one combined larger string
// the resulting string must be freed
char* string_concat(char* a, char* b);

#endif
