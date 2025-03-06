/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
array.h: Definition of dynamic_array and necessary functions
----------------------------------------------------------------*/

#ifndef ARRAY_H
#define ARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "print_functions.h"
#include "string_functions.h"

// Use struct for dynamic_array to keep track of size and capacity
typedef struct dynamic_array dynamic_array_t;

// Creates new empty dynamic array
dynamic_array_t *create_array();

// Adds element to array, realloc space if needed
void add_to_array(dynamic_array_t* array, business_t* element);

// Binary search used to find the position to add new value into array
int binary_search(const dynamic_array_t* array, const char* trading_name); 

// Finds index of query in array by binary search, then traverses around value to find other equalities
void find_and_traverse(const dynamic_array_t* array, const char* query, const char *outfile_name);

// Free the dynamically allocated memory used by array
void free_dynamic_array(dynamic_array_t* array);

#endif