/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
string_functions.c: Definition of functions to work with strings 
----------------------------------------------------------------*/

#include "string_functions.h"


// Custom strcmp function, same as strcmp, except checks for byte_comparisons

int strcmp_count(const char *query, const char *str2, int *comparison_count) {
    int result = 0;
    int n = strlen(query);
    
    while (n > 0) {
        // Increment the comparison count
        (*comparison_count)++;

        // Break characters not equal
        if (*query != *str2) {
            result = (unsigned char)*query - (unsigned char)*str2;
            break;
        }

        // Check if end of either string
        if (*query == '\0' || *str2 == '\0') {
            break; 
        }

        // Check next characters
        query++;
        str2++;
        n--;
    } 
    // Extra comparison for the NULL char comparison
    if (result == 0)
        (*comparison_count)++;

    // Same output as strcmp, 0 if equal
    return result;
}
