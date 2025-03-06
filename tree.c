/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
tree.c: Implementation of Radix Tree data structure 
----------------------------------------------------------------*/

#include "tree.h"
#include "read.h" // move this to read later


// Struct for the nodes in the radix tree
struct node {
    int prefix_bits; // Number of bits of shared prefix
    char *prefix; // Pointer to prefix
    business_t *data; // Pointer to business struct
    node_t *branchA; // Pointer to left value if the first different bit is 0
    node_t *branchB; // Pointer to right value if the first different bit is 1
};

// Struct for data node used in node_t struct
/*
This struct was not used as it was causing bugs
This was kept, but reverted to an older version of code
*/
struct data_node {
    business_t *data;
    data_node_t *next;

};
// Create node to be added to radix tree
node_t *create_node(business_t *business, int pbits) {

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    assert(new_node);
    // Initialise the values
    new_node -> prefix_bits = pbits;
    new_node -> prefix = strdup(business -> trading_name);
    new_node -> data = business;
    new_node -> branchA = NULL;
    new_node -> branchB = NULL;

    return new_node;
}

// Adds node to the radix tree and moves values around if needed
node_t *add_to_tree(node_t* root, business_t* business, int pbits) {

    // If empty
    if (root == NULL) {
        return create_node(business, pbits);
    }

    // Compare prefix with, new trading name
    int cmp = bit_cmp(root -> prefix, business -> trading_name);

    // If the new trading name has a smaller number of prefix bits, change the root
    if (cmp < root -> prefix_bits) {
        node_t *new_root = (node_t *)malloc(sizeof(node_t));
        assert(new_root);

        // Initialise new root values
        new_root -> prefix_bits = cmp;
        new_root -> prefix = root -> prefix;
        new_root -> data = NULL;
                
        // Get the values to insert left or right
        int bit_root = bit_at_pos(root -> prefix, cmp);
        
        // Check which branch to insert old root
        if (bit_root == 0) {
        new_root -> branchA = create_node(root -> data, root -> prefix_bits - cmp);
        } else {
        new_root -> branchB = create_node(root -> data, root -> prefix_bits - cmp);
        }

        // Check which branch to insert new businesses to 
        int bit_business = bit_at_pos(business -> trading_name, cmp);

        if (bit_business == 0) {
        new_root -> branchA = create_node(business, get_bit_length(business -> trading_name) - cmp);
        } else {
        new_root -> branchB = create_node(business, get_bit_length(business -> trading_name) - cmp);
        }
        free(root);
        return new_root;

    }

    // Get the new bit at pos
    int bit = bit_at_pos(business -> trading_name, cmp);

    // Recurse if there is no available data to check
    if (bit == 0) {
        root -> branchA = add_to_tree(root -> branchA, business, pbits - cmp);
    } else {
        root -> branchB = add_to_tree(root -> branchB, business, pbits - cmp);
    }

    return root;
}
// Returns the bit length of a string
int get_bit_length(const char* str) {
    return (strlen(str) + 1) * BIT_SIZE;
}

// Returns the bit at a given position
int bit_at_pos(const char *str, int pos) {
    // Handle invalid position
    if (pos < 0 || pos >  get_bit_length(str)) 
        return -1;
    

    // Calculate the byte index and bit index
    int byte_index = pos / 8;
    int bit_index = pos % 8;

    // Bitwise shifting to get desired bit
    unsigned char byte = str[byte_index];
    return (byte >> (7 - bit_index)) & 1;
}

// Compares the number of bits between two values
int bit_cmp(const char *prefix, const char *query) {
    
    int bit_difference = 0;
    int len1 = strlen(prefix);
    int len2 = strlen(query);

    int min_len;

    // Use the length of the shortest string
    if (len1 < len2) 
        min_len = len1;
    else 
        min_len = len2;

    // Go through each character
    for (int i = 0; i < min_len; i++) {
        char c1 = prefix[i];
        char c2 = query[i];
        // Go through each bit
        for (int j = 7; j >= 0; j--) {
            int bit1 = (c1 >> j) & 1;
            int bit2 = (c2 >> j) & 1;
            // Return difference if found
            if (bit1 != bit2) {
                return bit_difference + (7 - j);
            }
        }
        // ADD BIT_SIZE (8) for each loop
        bit_difference += BIT_SIZE; 
    }



    // If both strings are identical up to the length of the shorter string
    // Return the length of the shorter string in bits
    if (len1 < len2) {
        return bit_difference + (len2 - len1) * 8;
    } else if (len1 > len2) {
        return bit_difference + (len1 - len2) * 8;
    }

    // If both strings are identical, return the total number of bits
    return bit_difference;
}

// Compares the number of bits between two values but also changes the byte comparison count
int bit_cmp_count(const char *prefix, const char *query, int *bit_comparisons, int *byte_comparisons) {
    
    int bit_difference = 0;
    int len1 = strlen(prefix);
    int len2 = strlen(query);

    int min_len;

    // Use the length of the shortest string
    if (len1 < len2) 
        min_len = len1;
    else 
        min_len = len2;

    // Use the length of the shortest string
    int char_skips = (*bit_comparisons) / BIT_SIZE;
    int bit_skips = (*bit_comparisons) % BIT_SIZE;


    // Use the length of the shortest string
    for (int i = char_skips; i < min_len; i++) {
        char c1 = prefix[i];
        char c2 = query[i];
        // Increment byte comparisons
        (*byte_comparisons)++;
        for (int j = 7; j >= 0; j--) {
            // Skip number of bits already check
            while(bit_skips > 0) {
                j--;
                bit_skips --;
            }
            int bit1 = (c1 >> j) & 1;
            int bit2 = (c2 >> j) & 1;
            // Increment bit comparisons
            (*bit_comparisons)++;
            // Return difference if found
            if (bit1 != bit2) {
                return bit_difference + (7 - j); // Bits before they differ
            }
        }

        // ADD BIT_SIZE (8) for each loop
        bit_difference += BIT_SIZE;
    }



    // If both strings are identical up to the length of the shorter string
    // Return the length of the shorter string in bits
    if (len1 < len2) {
        return bit_difference + (len2 - len1) * 8;
    } else if (len1 > len2) {
        return bit_difference + (len1 - len2) * 8;
    }

    // If both strings are identical, return the total number of bits
    return bit_difference;
}

// Returns the first bit that differs between prefix and query
int get_diff_bit(const char *prefix, const char *query, int pbits, int *bit_comparisons, int *byte_comparisons) {
        
    // Calculate number of characters to go through
    int min_len = ((pbits + BIT_SIZE) / BIT_SIZE);
    int bit_count = 0;

    // If the prefix bits equal to length of prefix
    // Or prefix and query are equal return -1.
    if (pbits == get_bit_length(prefix) && strcmp(prefix, query) == 0)
        return -1;
    
    // Go through each character
    for (int i = 0; i < min_len; i++) {
        char c1 = prefix[i];
        char c2 = query[i];
        // Increment byte comparisons
        (*byte_comparisons)++;
        for (int j = 7; j >= 0; j--) {
            int bit1 = (c1 >> j) & 1;
            int bit2 = (c2 >> j) & 1;
                // If reached the number of prefix bits
            if (bit_count == pbits)
                return bit2;

            // If bits are not equal
            if (bit1 != bit2) 
                return bit2;

            // Increment bit comparisons
            (*bit_comparisons)++;
            bit_count++;
        }
    }    
    // Return the bit in query after the number of prefix bits
    return bit_at_pos(query, pbits);
}

// The search function for the radix tree, also keeps track of comparisons
void find_from_tree(node_t *root, const char *query, const char *outfile_name,
                    int bit_comparisons, int byte_comparisons, int string_comparisons) {
    assert(root);

    // new comparison counts to use when recursing
    int new_bitc = bit_comparisons;
    int new_bytec = byte_comparisons;
    int new_strinc = string_comparisons;
    
    // If data is found, compare to query
    if (root->data != NULL) {

        // Compare the bits, it returns length of query if equal
        int cmp = bit_cmp_count(root -> prefix, query, &new_bitc, &new_bytec);

        // - BIT_SIZE for null character
        int query_length = get_bit_length(query) - BIT_SIZE;

        new_strinc++;

        // Checks for equality
        if (cmp == query_length) {

            // Print the necessary information
            print_comparisons(query, new_bitc, new_bytec, new_strinc);
            print_to_file(root -> data, outfile_name);

            return;
        }

    } else {

        // Check the value of the bit that differs
        int diff = get_diff_bit(root -> prefix, query, root -> prefix_bits, &new_bitc, &new_bytec);

        // Go to branch depending on differing bit
        if (diff == 0) {
            find_from_tree(root -> branchA, query, outfile_name, new_bitc, new_bytec, new_strinc);
        } else {
            find_from_tree(root -> branchB, query, outfile_name, new_bitc, new_bytec, new_strinc);
        }

    }
}

// Frees all dynamically allocated memory
void free_tree(node_t *node) {
    if (node == NULL) {
        return;
    }

    // Free the dynamically allocated prefix
    if (node -> prefix != NULL) {
        free(node -> prefix);
    }


    if (node -> data != NULL) {

        business_t* business = node->data;
        
        // Free dynamically allocated fields in business
        free(business -> building_address);
        free(business -> clue_small_area);
        free(business -> business_address);
        free(business -> trading_name);
        free(business -> industry_description);
        free(business -> seating_type);

        // Free business struct
        free(business);
    }

    // Recursively free child nodes
    free_tree(node -> branchA);
    free_tree(node -> branchB);

    // Free the node
    free(node);
}