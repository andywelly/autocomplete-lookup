/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
print_functions.c: Implementation of functions that print values
----------------------------------------------------------------*/

#include "print_functions.h"


// Prints all business information to the output file
void print_to_file(business_t *business, const char *outfile_name) {
    // Open and assert output file
    FILE *outfile;
    outfile = fopen(outfile_name, "a");
    assert(outfile);

    // Print Data
    fprintf(outfile, "--> ");
    fprintf(outfile, "census_year: %d || block_id: %d || property_id: %d || base_property_id: %d || ", 
                    business -> census_year, business -> block_id, business -> property_id, business -> base_property_id);
    fprintf(outfile, "building_address: %s || clue_small_area: %s || business_address: %s || ", 
                    business -> building_address, business -> clue_small_area, business -> business_address);
    fprintf(outfile, "trading_name: %s || industry_code: %d || industry_description: %s || ",
                    business -> trading_name, business -> industry_code, business -> industry_description);
    fprintf(outfile, "seating_type: %s || number_of_seats: %d || longitude: %0.5lf || latitude: %0.5lf || \n",
                    business -> seating_type, business -> number_of_seats, business -> longitude, business -> latitude);
    
    // Close File
    fclose(outfile);
}

// Prints only the trading_name to the output file
void print_trading_name(const char *trading_name, const char *outfile_name) {

    // Open and asssert output file
    FILE *outfile;
    outfile = fopen(outfile_name, "a");
    assert(outfile);

    // Print trading name
    fprintf(outfile, "%s\n", trading_name);

    // Close File
    fclose(outfile);
}

// Prints comparisons to stdout
void print_comparisons(const char *query, int bit_comparisons, int byte_comparisons, int string_comparisons) {
    
    printf("%s --> b%d c%d s%d\n", query, bit_comparisons, byte_comparisons, string_comparisons);

}