/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
tree.h: Definition of Radix Tree data structure 
----------------------------------------------------------------*/

#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "print_functions.h"
#include "string_functions.h"

#define BIT_SIZE 8


// Struct for each node in the radix tree
typedef struct node node_t;

// Struct for data node used in node_t struct
/*
This struct was not used as it was causing bugs
This was kept, but reverted to an older version of code
*/
typedef struct data_node data_node_t;

// Create node to be added to radix tree
node_t *create_node(business_t *business, int pbits);

// Adds node to the radix tree and moves values around if needed
node_t *add_to_tree(node_t* node, business_t* business, int pbits);

// Returns the bit length of a string
int get_bit_length(const char* str);

// Returns the bit at a given position
int bit_at_pos(const char *str, int pos);

// Compares the number of bits between two values
int bit_cmp(const char *prefix, const char *query);

// Compares the number of bits between two values but also changes the byte comparison count
int bit_cmp_count(const char *prefix, const char *query, int *bit_comparisons, int *byte_comparisons);

// Returns the first bit that differs between prefix and query
int get_diff_bit(const char *prefix, const char *query, int pbits, int *bit_comparisons, int *byte_comparisons);

// The search function for the radix tree, also keeps track of comparisons
void find_from_tree(node_t *root, const char *query, const char *outfile_name,
                    int bit_comparisons, int byte_comparisons, int string_comparison);

// Frees all dynamically allocated memory
void free_tree(node_t *root);


#endif 