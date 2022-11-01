#include <stdbool.h>
#include <stddef.h>

#include <matrix-multiplication.h>
#include <fixed-point.h>
#include <float16.h>

short calculateOffset(char row, char col, char rows, char columns) {
    return row*columns+col;
}

// return 0 for fail, 1 for success
int Matrix_Mul(
    float *A,
    float *B,
    float *Result,
    int rows_of_A,
    int columns_of_A,
    int rows_of_B,
    int columns_of_B,
    bool Fix_Or_Float16 // true ==> fixed point, false ==> float16
) {
    // first check that matrix dimensions are suitable for multiplication:
    // columns_of_A == rows_of_B

    if (columns_of_A != rows_of_B)
    {
        return 0;
    }

    // if A or B are NULL pointers,
    // we can't do anything
    if (A == NULL || B == NULL) {
        return 0;
    }

    // if Result is a NULL pointer, 
    // there is no point calculating anything 
    // since we cannot provide the result
    if (Result == NULL) {
        return 0;
    }

    if (Fix_Or_Float16) {
        // perform calculations using fixed point
        for (char i = 0; i < rows_of_A; ++i) { // row i of A
            for (char k = 0; k < columns_of_B; ++k) { // column k of B
                FixedPoint elem = 0;
                for (char j = 0; j < columns_of_A; ++j) { // j'th element in row i of A OR j'th element in column k of B
                    elem = FixedPointAdd(
                        elem,
                        FixedPointMultiply(
                            FloatToFixedPoint(
                                A[calculateOffset(i, j, rows_of_A, columns_of_A)]
                            ),
                            FloatToFixedPoint(
                                B[calculateOffset(j, k, rows_of_B, columns_of_B)]
                            )
                        )
                    );
                }
                Result[
                    calculateOffset(i, k, rows_of_A, columns_of_B)
                ] = FixedPointToFloat(elem);
            }
        }
    } else {
        // perform calculations using float16
        for (char i = 0; i < rows_of_A; ++i) { // row i of A
            for (char k = 0; k < columns_of_B; ++k) {  // column k of B
                Float16 elem = 0.0;
                for (char j = 0; j < columns_of_A; ++j) { // j'th element in row i of A OR j'th element in column k of B
                    elem = Float16Add(
                        elem,
                        Float16Multiply(
                            FloatToFloat16(
                                A[calculateOffset(i, j, rows_of_A, columns_of_A)]
                            ),
                            FloatToFloat16(
                                B[calculateOffset(j, k, rows_of_B, columns_of_B)]
                            )
                        )
                    );
                }
                Result[
                    calculateOffset(i, k, rows_of_A, columns_of_B)
                ] = Float16ToFloat(elem);
            }
        }
    }
    return 1;
}