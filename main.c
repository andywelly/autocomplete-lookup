/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
main.c: Entry Point of the code
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "array.h"
#include "business.h"
#include "print_functions.h"
#include "read.h"
#include "string_functions.h"
#include "tree.h"

#define MIN_ARGS 4
#define MAX_STRING_LENGTH 128

int main(int argc, char const *argv[]) {
    
    // Checks if the necessary inputs are given
    if (argc < MIN_ARGS) {
        printf("Error: Only %d arguments given, at least %d arguments needed", argc, MIN_ARGS);
        return 1;
    }

    const char* infile_name = argv[2];
    const char* outfile_name = argv[3];

    int stage = atoi(argv[1]);

    if (stage == 2) {
        
        // Checks if infile exists
        FILE *infile = fopen(infile_name, "r");
        assert(infile);
        
        // Reads csv file and adds data to dynamic_array
        dynamic_array_t *business_array = read_to_array(infile);

        // Close file
        fclose(infile);

        // Opens the output file and clear it
        FILE *outfile = fopen(outfile_name, "w");
        assert(outfile);
        fclose(outfile);

        
        char query[MAX_STRING_LENGTH];

        // Get query from stdin
        while (fgets(query, sizeof(query), stdin)) {

            // remove trailing newline char
            query[strcspn(query, "\n")] = '\0';

            // exit loop if empty string
            if (query[0] == '\0') {
                break; 
            }
            
            // Print query to the output file
            print_trading_name(query, outfile_name);
            
            // Find and print any matches into output file
            find_and_traverse(business_array, query, outfile_name);
            
        }
        
        // Free all dynamically allocated memory
        free_dynamic_array(business_array);

    } else if (stage == 3) {

        FILE *infile = fopen(infile_name, "r");
        assert(infile);

        node_t *root = read_to_tree(infile);
        assert(root);

        fclose(infile);

         // Opens the output file and clear it
        FILE *outfile = fopen(outfile_name, "w");
        assert(outfile);
        fclose(outfile);

        
        char query[MAX_STRING_LENGTH];

        // Get query from stdin
        while (fgets(query, sizeof(query), stdin)) {

            // remove trailing newline char
            query[strcspn(query, "\n")] = '\0';

            // exit loop if empty string
            if (query[0] == '\0') {
                break; 
            }
            
            // Print query to the output file
            print_trading_name(query, outfile_name);

            // Find and print any matches into output file
            find_from_tree(root, query, outfile_name, 0, 0, 0);
            

        }
        
        // Free all dynamically allocated memory
        free_tree(root);

    } else {
        // If the stage number is not valid return an error
        printf("Error: Enter a valid stage");
        return 1;
    }

    return 0;
}
