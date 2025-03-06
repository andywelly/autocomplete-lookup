/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
print_functions.h Definition of functions that print values
----------------------------------------------------------------*/

#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "business.h"
#include "business.c"
#include "tree.h"

// Prints all business information to the output file
void print_to_file(business_t *business, const char *outfile_name);

// Prints only the trading_name to the output file
void print_trading_name(const char *trading_name, const char *outfile_name);

// Prints comparisons to stdout
void print_comparisons(const char *query, int bit_comparisons, int byte_comparisons, int string_comparisons);


#endif