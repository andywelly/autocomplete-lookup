# Autocomplete Lookup

This repository contains the code and report for the Algorithms and Data Structures Subjec, focusing on implementing autocomplete lookup using two different data structures: a sorted array and a radix tree.

## Description

This C project implements an autocomplete feature using both sorted arrays and radix trees, enabling a comparative analysis of algorithmic efficiency. A detailed report compares the performance of these data structures using Big-O notation, highlighting the trade-offs between them. This project significantly enhanced my understanding of algorithmic efficiency and the importance of data structure selection. Furthermore, it provided valuable experience in manipulating data into various types to optimize performance.

## Project Overview

This assignment involved two main stages:

1.  **Stage 2: Sorted Array Implementation:**
    * Reading data from a CSV file.
    * Storing business data in a dynamically resized, sorted array.
    * Implementing binary search for efficient insertion, find, and traverse operations.
2.  **Stage 3: Radix Tree Implementation:**
    * Reading data from the same CSV file.
    * Storing business data in a radix tree, using binary representations of characters for branching.
    * Implementing search functionality to find matching entries.

## Implementation Details:

* **Radix Tree Node Structure:**
    * `prefix_bits`: Integer representing the number of common prefix bits.
    * `prefix`: Dynamically allocated character array containing the common prefix.
    * `branchA`: Pointer to the node for bit '0'.
    * `branchB`: Pointer to the node for bit '1'.
    * `data_list`: Pointer to a list of associated data items.
* **Bit Manipulation:**
    * Uses bitwise operators (`&`, `|`, `<<`, `>>`) for efficient bit extraction and manipulation.
    * `getBit(key, n)` and `splitStem(key, start, length)` helper functions.
* **Input Data:**
    * Reads data from CSV files containing information about cafes and restaurants.
    * Handles CSV fields with commas enclosed in double quotes.
    * Parses and stores data with appropriate data types.
* **Output:**
    * Outputs matching records to an output file in a specified format.
    * Outputs the number of bit, character, and string comparisons to standard output for performance analysis.

## Compilation: 

To compile the programs, navigate to the project root directory and run:

```bash
make
```
This will generate two executable files: dict2 (Stage 2) and dict3 (Stage 3).


Usage:

* Stage 2 (Sorted Array):
```bash
./dict2 2 <datafile> <outputfile> < queryfile
```
* Stage 3 (Radix Tree):
```bash
./dict3 3 <datafile> <outputfile> < queryfile
```
* datafile: Path to the input CSV file.
* outputfile: Path to the output file.
* queryfile: Path to the file containing queries.

Example Execution:
```bash
make -B dict3
./dict3 3 tests/dataset_1.csv output.out < tests/test1.in > output.stdout.out
```

## Dataset:

* Data source: City of Melbourne Open Data website.
* Dataset: Cafes and Restaurants with Seating Capacity.
* Fields:
  * census_year
  * block_id
  * property_id
  * base_property_id
  * building_address
  * clue_small_area
  * business_address
  * trading_name
  * industry_code
  * industry_description
  * seating_type
  * number_of_seats
  * longitude
  * latitude.

## Notes:

* The programs are implemented in C.
* The code is well-commented and follows good coding practices.
* The programs handle CSV data with quoted fields.
* The programs output performance metrics to standard output.
* Use the same dataset file number for the test file number eg. Use dataset_1.csv with tests/test1.in

