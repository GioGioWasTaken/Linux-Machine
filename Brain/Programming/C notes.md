- Header files contain declarations and definitions that are shared across multiple `.c` or `.cpp` files. Some examples of things they include are:
  -  Function Declarations: Specify the names, return types, and parameters of functions.
  -  Macro Definitions: Define constants and reusable code snippets.
  -  Data Structures: Define structures, unions, and enumerations.
  -  Constants: Define constant values.
  ```C
    #ifndef EXAMPLE_H
    #define EXAMPLE_H

    // Function Declarations
    void print_message();
    int add(int a, int b);

    // Macro Definitions
    #define PI 3.14159
    #define MAX(a, b) ((a) > (b) ? (a) : (b))

    // Data Structure Definitions
    typedef struct {
        int id;
        char name[50];
        float salary;
    } Employee;

    typedef enum {
        RED,
        GREEN,
        BLUE
    } Color;

    // Constants
    const int BUFFER_SIZE = 1024;
  ```

- 
