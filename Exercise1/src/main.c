#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <matrix-multiplication.h>
#include <serde.h>

// 8K should be plenty
#define BUFSIZE 8192

// 16 * 16 matrix should be big enough
#define MATRIX_MAX_ELEMS 256

const char* helpText = "\
Flags: \n\
-h : print help text \n\
-f : use fixed point numbers for intermediate calculation (half precision float used by default) \n\
-m (plain|matlab) : input/output matrix format (only matlab is supported) (default = matlab) \n\
";

void readMatrix(char* buf, enum SerializationFormat mode);

int main(int argc, char** argv) {
    char bufA[BUFSIZE];
    char bufB[BUFSIZE];
    char bufR[BUFSIZE];

    float matA[MATRIX_MAX_ELEMS];
    float matB[MATRIX_MAX_ELEMS];
    float matR[MATRIX_MAX_ELEMS];

    enum SerializationFormat mode = Matlab;
    int c;
    int rowsA, rowsB, rowsR, colsA, colsB, colsR = 0;
    bool useFixedPoint = false;

    // handle command line flags first
    while ( (c = getopt(argc, argv, "fhm:")) != -1) {
        switch (c) {
        case 'f':
            useFixedPoint = true;
            break;
        case 'm':
            if (strcmp(optarg, "plain") == 0) {
                mode = Plain;
            } else if (strcmp(optarg, "matlab") == 0) {
                mode = Matlab;
            } else {
                printf("unknown mode: %s\n", optarg);
            }
            break;
        case 'h':
            fprintf(stderr, helpText, NULL);
            return 0;
        }
    }

    if (mode == Plain) {
        printf("Plain matrix format currently not supported, please use matlab format instead.\n");
        return 1;
    }
    
    printf("Enter matrix A:\n");
    readMatrix(bufA, mode);

    printf("Enter matrix B:\n");
    readMatrix(bufB, mode);

    if (unmarshalMatrix(bufA, mode, matA, &rowsA, &colsA) == 0) {
        printf("failed to unmarshal matrix A\n");
    }

    if (unmarshalMatrix(bufB, mode, matB, &rowsB, &colsB) == 0) {
        printf("failed to unmarshal matrix B\n");
    }

    int res = Matrix_Mul(matA, matB, matR, rowsA, colsA, rowsB, colsB, useFixedPoint);
    if (res == 0) { 
        printf("failed to multiply matrices\n"); 
        return 1; 
    }

    res = marshalMatrix(bufR, mode, matR, rowsA, colsB);
    if (res == 0) {
        printf("failed to marshal result matrix\n");
        return 1;
    }

    printf("result:\n%s\n", bufR);
    return 0;
}

void readMatrixPlain(char* buf) {
    char lineBuffer[BUFSIZE];
    // read until totally empty line
    // TODO: implement
}

void readMatrixMatlab(char* buf) {
    // read a single line into the buffer
    fgets(buf, BUFSIZE, stdin);
}

void readMatrix(char* buf, enum SerializationFormat mode) {
    switch (mode) {
    case Plain:
        readMatrixPlain(buf);
        break;
    case Matlab:
        readMatrixMatlab(buf);
        break;
    }
    return;
}
