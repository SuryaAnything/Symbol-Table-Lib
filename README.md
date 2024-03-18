# Symbol Table Library

## Overview
This project provides a symbol table library implemented in C. It consists of two main files: `symbol.h` and `symbol.c`. The library offers functionalities for managing symbol tables, variable assignment, type conversion, and error handling.

## Files
- `symbol.h`: Header file containing the declarations of structures, macros, and function prototypes.
- `symbol.c`: Source file containing the implementations of the functions declared in `symbol.h`.

## Usage
To use the symbol table library in your C project, follow these steps:
1. Include the `symbol.h` header file in your source files where symbol table functionalities are needed.
    ```c
    #include "symbol.h"
    ```

2. To link symbol.c with your project using CMake, include it as a source file in the add_executable command in your CMakeLists.txt.
   

3. Utilize the provided functions and macros to manage symbol tables, assign values, and perform type conversions as per your requirements.

## Functionality
- **Symbol Table Management**: Functions for initializing, ending, and accessing scopes within the symbol table.
- **Variable Assignment**: Functions to assign values to variables within the symbol table.
- **Type Conversion**: Functions for converting data types (e.g., integer to string, string to double).
- **Error Handling**: Macros for throwing exceptions in case of errors (e.g., overflow, parse error, allocation failure).

## Example
```c
#include "symbol.h"
#include <stdio.h>

int main() {
    // Initialize a scope
    begin;

    // Assign values to variables
    assign(Integer, "x", "10");
    assign(Double, "pi", "3.14");

    // Access variables
    int x = integer_cast(read("x"));
    double pi = double_cast(read("pi"));

    // Print values
    printf("x = %d\n", x);
    printf("pi = %f\n", pi);

    // End scope
    end;

    return 0;
}
