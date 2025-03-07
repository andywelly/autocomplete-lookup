/*-------------------------------------------------------------- 
Assignment 2: Autocomplete Lookup
array.c: Implementation of dynamic_array and necessary functions
----------------------------------------------------------------*/

#include "array.h"


// Use struct for dynamic_array to keep track of size and capacity
struct dynamic_array{
    business_t **data; // array of businesses
    int size; // current size of array
    int capacity; // maximum capacity of array
};


// Creates new empty dynamic array
dynamic_array_t *create_array() {

    // dynamically allocate memory for the struct
    dynamic_array_t* array = (dynamic_array_t*)malloc(sizeof(dynamic_array_t));
    assert(array);
    // initialise values
    array -> data = NULL;
    array -> size = 0;
    array -> capacity = 0;

    return array;
}

// Adds element to array, realloc space if needed
void add_to_array(dynamic_array_t* array, business_t* element) {

    // Check if array exists
    assert(array);
    assert(element);

    // Resize array if array is full
    if (array -> size >= array -> capacity) {
        
        // Double new capacity
        int new_capacity;
        if (array -> capacity == 0) {
            new_capacity = 1; // if capacity is 0, set to 1
        } else {
            new_capacity = array -> capacity * 2;
        }   

        // Realloc space for the new business
        business_t** new_data = (business_t**)realloc(array->data, new_capacity * sizeof(business_t*));
        assert(new_data);

        // Update the dynamic array
        array -> data = new_data;
        array -> capacity = new_capacity;
    }

    // Insert the new element in sorted array, based on trading_name
    // If identical elements already present, place it after
    int position = binary_search(array, element -> trading_name);

    // Shift elements to make space for the new element
    for (int i = array -> size; i > position; i--) {
        array -> data[i] = array -> data[i - 1];
    }

    // Add element to the dynamic array
    array -> data[position] = element;

    // Increment size
    array -> size++;
}

// Binary search used to find the position to add new value into array
int binary_search(const dynamic_array_t* array, const char* trading_name) {

    int low = 0;
    int high = array -> size - 1;

    while (low <= high) {
        
        // Find the middle value
        int mid = low + (high - low) / 2;
        // Compare trading_name query to the middle value
        int cmp = strcmp(trading_name, array -> data[mid] -> trading_name); 
        
        if (cmp == 0) {

            // Create temporary value to check if any identical values after
            int temp = mid;
            // Place it after the last equal trading_name
            while (strcmp(trading_name, array -> data[temp] -> trading_name) == 0) {
                temp++;
            }

            // Return position to insert the new value
            return temp; 

        // Continue searching
        } else if (cmp < 0) {
            high = mid - 1; // Search in the left half
        } else {
            low = mid + 1;  // Search in the right half
        }

    }
    // If not found, 'low' (0) is the correct position to insert the new element
    return low;
}


// Finds index of query in array by binary search, then traverses around value to find other equalities
void find_and_traverse(const dynamic_array_t* array, const char* query, const char *outfile_name) {

    // Initialise comparison counts
    int string_comparisons = 0;
    int byte_comparisons = 0;
    int bit_comparisons = 0;

    // Initailise low and high values
    int low = 0;
    int high = array -> size - 1;

    
    while (low <= high) {


        int mid = low + (high - low) / 2;

        // Customer strcmp_count, same as strcmp, but checks byte_comparisons
        int cmp = strcmp_count(query, array -> data[mid] -> trading_name, &byte_comparisons);

        // Every iteration of the binary search adds string comparson
        string_comparisons++;

        // When query is found traverses to the left and right of index
        if (cmp == 0) {
            
            
            int left = mid;

            // If left not the first value, adds a string_comparison
            if (left != 0) 
                string_comparisons++;

            // Traverses left to check for matches
            while (left > 0 && strcmp_count(query, array -> data[left - 1] -> trading_name, &byte_comparisons) == 0) {
                left --;
                string_comparisons++;
            }

            // Print starting from the left most value
            while (left < mid) {
                print_to_file(array -> data[left], outfile_name);
                left ++;
            }

            // Print middle value
            print_to_file(array -> data[mid], outfile_name);

            
            int right = mid;

            // If right not the last value, add a string_comparison
            if (right != array -> size - 1)
                string_comparisons++;

            // Traverse right and print any matches
            while (right < array -> size - 1 && strcmp_count(query, array -> data[right + 1] -> trading_name, &byte_comparisons) == 0) {
                right ++;
                string_comparisons++;
                print_to_file(array -> data[right], outfile_name);
            }

            // Exit loop once found
            break;

        // Change the search scope
        } else if (cmp < 0) {
            high = mid - 1; // Search in the left half

        } else {
            low = mid + 1;  // Search in the right half
        }

    }

    
    bit_comparisons = byte_comparisons * BIT_SIZE;

    // Prints to stdout
    print_comparisons(query, bit_comparisons, byte_comparisons, string_comparisons);
        
}



// Free the dynamically allocated memory used by array
void free_dynamic_array(dynamic_array_t* array) {
    assert(array);

    // Free the dynamically allocated business_t pointers in the array
    for (int i = 0; i < array -> size; i++) {

        business_t* business = array->data[i];
        
        // Free the dynamically allocated fields in business
        free(business -> building_address);
        free(business -> clue_small_area);
        free(business -> business_address);
        free(business -> trading_name);
        free(business -> industry_description);
        free(business -> seating_type);

        // Free the actual business struct
        free(business);
    }

    // Free the array's data array
    free(array -> data);

    // Finally, free the dynamic_array_t structure itself
    free(array);
}