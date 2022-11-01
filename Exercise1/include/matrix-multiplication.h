#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <stdbool.h>


short calculateOffset(char row, char col, char rows, char columns);

// returns 0 for fail, 1 for success
int Matrix_Mul(
    float* A, 
    float* B, 
    float* Result, 
    int rows_of_A, 
    int columns_of_A, 
    int rows_of_B,
    int columns_of_B,
    bool Fix_Or_Float16 // true ==> fixed point, false ==> float16
);

#endif