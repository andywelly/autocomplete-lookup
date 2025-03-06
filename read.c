/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
read.c: Implementation of functions to read data from file
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "read.h"
#include "business.h"

// Reads the input file and adds sorted data into dynamic array
dynamic_array_t *read_to_array(FILE *infile) {

    // Create array
    dynamic_array_t *business_array = create_array();

    // There is an assert() in create_array() but just to be safe
    assert(business_array); 

    // Buffer to store each line
    char line[MAX_INPUT];

    // Skip header line
    fgets(line, sizeof(line), infile);

    
    while (fgets(line, sizeof(line), infile)) {
        
        // Each iteration of outer loop adds business to list
        business_t *business = (business_t*)malloc(sizeof(*business));
        assert(business);

        char *token;
        int case_count = 0; // case_count to use for switch block
    
        // Reads line until ","
        token = strtok(line, ",");

        // Loops until entire line is read
        while (token != NULL) {

            // If data is enclosed in quotation marks
            if (token[0] == '"') {
                //skip over initial quote
                token ++;

                // Get strings to concatenate
                char *first_value = strdup(token);
                assert(first_value);
                char *comma = ",";
                token = strtok(NULL, ",");
                char *second_value = strdup(token);
                assert(second_value);

                // Allocate memory for combined_string
                size_t combined_length = strlen(first_value) + strlen(comma) + strlen(second_value) + 1;
                char *combined_string = (char *) malloc(combined_length);
                assert(combined_string);

                // Concatenates the strings
                strcpy(combined_string, first_value);
                strcat(combined_string, comma);
                strcat(combined_string, second_value);

                // Locates and Removes enclosing quotation mark
                char *closing_quote = strchr(combined_string, '"');
                *closing_quote = '\0';
                
                // Switch block to assign data to business struct members
                switch (case_count) {
                case 0: business -> census_year = atoi(combined_string); break;
                case 1: business -> block_id = atoi(combined_string); break;
                case 2: business -> property_id = atoi(combined_string); break;
                case 3: business -> base_property_id = atoi(combined_string); break;
                case 4: business -> building_address = strdup(combined_string); 
                    assert(business -> building_address);
                    break;
                case 5: business -> clue_small_area = strdup(combined_string); 
                    assert(business -> clue_small_area);
                    break;  
                case 6: business -> business_address = strdup(combined_string);
                    assert(business -> building_address);
                    break;
                case 7: business -> trading_name = strdup(combined_string); 
                    assert(business -> trading_name);
                    break;
                case 8: business -> industry_code = atoi(combined_string); break;
                case 9: business -> industry_description = strdup(combined_string);
                    assert(business -> industry_description);
                    break;
                case 10: business -> seating_type = strdup(combined_string);
                    assert(business -> seating_type);
                    break;
                case 11: business -> number_of_seats = atoi(combined_string); break;
                case 12: business -> longitude = atof(combined_string); break;
                case 13: business -> latitude = atof(combined_string); break;
                } 

                // Free malloced memory not needed since strdup used
                free(first_value);
                free(second_value);
                free(combined_string);
                
            } else { // If not enclosed in quotation marks

                // Straight to switch block to assign data
                switch (case_count) {
                    case 0: business -> census_year = atoi(token); break;
                    case 1: business -> block_id = atoi(token); break;
                    case 2: business -> property_id = atoi(token); break;
                    case 3: business -> base_property_id = atoi(token); break;
                    case 4: business -> building_address = strdup(token); 
                    assert(business -> building_address);
                    break;
                case 5: business -> clue_small_area = strdup(token); 
                    assert(business -> clue_small_area);
                    break;  
                case 6: business -> business_address = strdup(token);
                    assert(business -> building_address);
                    break;
                case 7: business -> trading_name = strdup(token); 
                    assert(business -> trading_name);
                    break;
                case 8: business -> industry_code = atoi(token); break;
                case 9: business -> industry_description = strdup(token);
                    assert(business -> industry_description);
                    break;
                case 10: business -> seating_type = strdup(token);
                    assert(business -> seating_type);
                    break;
                    case 11: business -> number_of_seats = atoi(token); break;
                    case 12: business -> longitude = atof(token); break;
                    case 13: business -> latitude = atof(token); break;
                }
            }
            // Increment case count for switch block
            case_count ++;
            // Get next data value
            token = strtok(NULL, ",");  
        }
        
        // Add element to the business array 
        add_to_array(business_array, business);

    }
    
    // Return business_array containing information of all businesses
    return business_array;
}




// Reads the input file and adds data into the radix tree
node_t *read_to_tree(FILE *infile) {

    // Create root
    node_t *root = NULL;

    // Buffer to store each line
    char line[MAX_INPUT];

    // Skip header line
    fgets(line, sizeof(line), infile);

    while (fgets(line, sizeof(line), infile)) {
        
        // Each iteration of outer loop adds business to list
        business_t *business = (business_t*)malloc(sizeof(*business));
        assert(business);

        char *token;
        int case_count = 0; // case_count to use for switch block
    
        // Reads line until ","
        token = strtok(line, ",");

        // Loops until entire line is read
        while (token != NULL) {

            // If data is enclosed in quotation marks
            if (token[0] == '"') {
                //skip over initial quote
                token ++;

                // Get strings to concatenate
                char *first_value = strdup(token);
                assert(first_value);
                char *comma = ",";
                token = strtok(NULL, ",");
                char *second_value = strdup(token);
                assert(second_value);

                // Allocate memory for combined_string
                size_t combined_length = strlen(first_value) + strlen(comma) + strlen(second_value) + 1;
                char *combined_string = (char *) malloc(combined_length);
                assert(combined_string);

                // Concatenates the strings
                strcpy(combined_string, first_value);
                strcat(combined_string, comma);
                strcat(combined_string, second_value);

                // Locates and Removes enclosing quotation mark
                char *closing_quote = strchr(combined_string, '"');
                *closing_quote = '\0';
                
                // Switch block to assign data to business struct members
                switch (case_count) {
                case 0: business -> census_year = atoi(combined_string); break;
                case 1: business -> block_id = atoi(combined_string); break;
                case 2: business -> property_id = atoi(combined_string); break;
                case 3: business -> base_property_id = atoi(combined_string); break;
                case 4: business -> building_address = strdup(combined_string); 
                    assert(business -> building_address);
                    break;
                case 5: business -> clue_small_area = strdup(combined_string); 
                    assert(business -> clue_small_area);
                    break;  
                case 6: business -> business_address = strdup(combined_string);
                    assert(business -> building_address);
                    break;
                case 7: business -> trading_name = strdup(combined_string); 
                    assert(business -> trading_name);
                    break;
                case 8: business -> industry_code = atoi(combined_string); break;
                case 9: business -> industry_description = strdup(combined_string);
                    assert(business -> industry_description);
                    break;
                case 10: business -> seating_type = strdup(combined_string);
                    assert(business -> seating_type);
                    break;
                case 11: business -> number_of_seats = atoi(combined_string); break;
                case 12: business -> longitude = atof(combined_string); break;
                case 13: business -> latitude = atof(combined_string); break;
                } 

                // Free malloced memory not needed since strdup used
                free(first_value);
                free(second_value);
                free(combined_string);
                
            } else { // If not enclosed in quotation marks

                // Straight to switch block to assign data
                switch (case_count) {
                    case 0: business -> census_year = atoi(token); break;
                    case 1: business -> block_id = atoi(token); break;
                    case 2: business -> property_id = atoi(token); break;
                    case 3: business -> base_property_id = atoi(token); break;
                    case 4: business -> building_address = strdup(token); 
                    assert(business -> building_address);
                    break;
                case 5: business -> clue_small_area = strdup(token); 
                    assert(business -> clue_small_area);
                    break;  
                case 6: business -> business_address = strdup(token);
                    assert(business -> building_address);
                    break;
                case 7: business -> trading_name = strdup(token); 
                    assert(business -> trading_name);
                    break;
                case 8: business -> industry_code = atoi(token); break;
                case 9: business -> industry_description = strdup(token);
                    assert(business -> industry_description);
                    break;
                case 10: business -> seating_type = strdup(token);
                    assert(business -> seating_type);
                    break;
                    case 11: business -> number_of_seats = atoi(token); break;
                    case 12: business -> longitude = atof(token); break;
                    case 13: business -> latitude = atof(token); break;
                }
            }
            // Increment case count for switch block
            case_count ++;
            // Get next data value
            token = strtok(NULL, ",");  
        }
        

        // Get the number of bit of the trading name
        int num_bits = get_bit_length(business -> trading_name);

        // Add element to the radix tree
        root = add_to_tree(root, business, num_bits);


    }
    
    // Return root of the radix tree
    return root;
}

