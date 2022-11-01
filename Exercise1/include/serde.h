#ifndef MATRIX_MULTIPLICATION_SERDE_H
#define MATRIX_MULTIPLICATION_SERDE_H

// Plain format means something like this:
// 1 2
// 3 4
// 5 6
// i.e. one line represents a row with elements separated by whitespace
// Matlab format means something like this:
// [1 2; 3 4; 5 6]
enum SerializationFormat {Plain = 0, Matlab = 1};

// Parse a matrix given as a string, return 0 for fail, 1 for success. 
// Matrix elements will be copied to float array given as third argument,
// number of rows will be assigned to the fourth argument, and
// number of columns will be assigned to the fifth argument.
int unmarshalMatrix(char* buf, enum SerializationFormat format, float* matrix, int* rows, int* columns);

// serialize, return 0 for fail, 1 for success
int marshalMatrix(char* buf, enum SerializationFormat format, float* matrix, int rows, int columns);

#endif