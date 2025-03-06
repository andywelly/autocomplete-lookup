/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
business.c: Implementation of the business struct
----------------------------------------------------------------*/

#include "business.h"

// business struct to store all business data
struct business{
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    char *building_address;
    char *clue_small_area;
    char *business_address;
    char *trading_name;
    int industry_code;
    char *industry_description;
    char *seating_type;
    int number_of_seats;
    double longitude;
    double latitude;
};
