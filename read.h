/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
read.h Definition of functions to read from file
----------------------------------------------------------------*/

#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"

#define MAX_INPUT 512 // Given in Specifications

// Reads the input file and adds sorted data into dynamic array
dynamic_array_t *read_to_array(FILE *infile);

// Reads the input file and adds data into the radix tree
node_t *read_to_tree(FILE *infile);

#endif