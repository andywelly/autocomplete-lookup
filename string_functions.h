/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
string_functions.c: Implementation of functions that work with strings
----------------------------------------------------------------*/

#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <string.h>

// Custom strcmp function, same as strcmp, except checks for byte_comparisons
/*
Inspired by https://github.com/gcc-mirror/gcc/blob/master/libiberty/strncmp.c
Available in public domain
*/
int strcmp_count(const char *prefix, const char *str2, int *comparison_count);

#endif