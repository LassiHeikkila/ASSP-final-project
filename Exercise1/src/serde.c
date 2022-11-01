#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <serde.h>
#include <matrix-multiplication.h>

int unmarshalPlainMatrix(char* buf, float* matrix, int* rows, int* columns);
int unmarshalMatlabMatrix(char* buf, float* matrix, int* rows, int* columns);

int marshalPlainMatrix(char* buf, float* matrix, int rows, int columns);
int marshalMatlabMatrix(char* buf, float* matrix, int rows, int columns);

int countChars(char* in, char c);
float getFloatFromStringSlice(char* begin, int length);

// deserialize, return 0 for fail, 1 for success
int unmarshalMatrix(char* buf, enum SerializationFormat format, float* matrix, int* rows, int* columns) {
    switch (format) {
    case Plain:
        return unmarshalPlainMatrix(buf, matrix, rows, columns);
    case Matlab:
        return unmarshalMatlabMatrix(buf, matrix, rows, columns);
    default:
        // don't know how to unmarshal other formats
        return 0;
    }
}

// serialize, return 0 for fail, 1 for success
int marshalMatrix(char* buf, enum SerializationFormat format, float* matrix, int rows, int columns) {
    switch (format) {
    case Plain:
        return marshalPlainMatrix(buf, matrix, rows, columns);
    case Matlab:
        return marshalMatlabMatrix(buf, matrix, rows, columns);
    default:
        // don'ẗ know how to marshal other formats
        return 0;
    }
}

// assumes that matrix has regular size, so first row has just as many elements as any other row.
int unmarshalPlainMatrix(char* buf, float* matrix, int* rows, int* columns) {
    int rowCount, columnCount = 0;
    // example:
    // 1 2
    // 3 4
    // 5 6
    int i = 0;
    while (*buf != '\00') {
        float v = 0.0;
        sscanf(buf, "%f", &v);
        matrix[i] = v;
        ++i;
        buf++;
    }
    return 0;
}

int unmarshalMatlabMatrix(char* buf, float* matrix, int* rows, int* columns) { 
    // example:
    // [1 2; 3 4; 5 6]
    int rowCount, columnCount = 0;

    // find opening "["
    char* begin = strchr(buf, '[');
    if (begin == NULL) return 0;

    // find closing "]"
    char* end = strchr(begin, ']');
    if (end == NULL) return 0;

    // count number of semi-colons and add 1 ==> number of rows
    rowCount = countChars(buf, ';') + 1;

    // for the string between opening and closing square brackets
    // iterate by finding next space or semi-colon, and parsing the content as float
    int i = 0;
    for (char* c = begin+1; c < end-1; ) {
        int len = strcspn(c, " ;]");
        if (len == 0) {
            ++c;
            continue;
        }
        
        float f = getFloatFromStringSlice(c, len);
        matrix[i] = f;
        c += len;
        ++i;
    }

    // assume that the matrix has uniformly sized rows
    columnCount = i/rowCount;

    if (rows != NULL) {
        *rows = rowCount;
    }
    if (columns != NULL) {
        *columns = columnCount;
    }
    return 1;
}

int marshalPlainMatrix(char* buf, float* matrix, int rows, int columns) {
    // example:
    // 1 2
    // 3 4
    // 5 6
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            sprintf(buf, "%f ", matrix[calculateOffset(i, j, rows, columns)]);
        }
        sprintf(buf, "\n");
    }
    return 1;
}

int marshalMatlabMatrix(char* buf, float* matrix, int rows, int columns) {
    // example:
    // [1 2; 3 4; 5 6]
    strcat(buf, "[");
    char f[32];
    for (int i = 0; i < rows; ++i) {
        if (i != 0) strcat(buf, ";");
        for (int j = 0; j < columns; ++j) {
            sprintf(f, " %f", matrix[calculateOffset(i, j, rows, columns)]);
            strcat(buf, f);
        }
    }
    strcat(buf, " ]");
    return 1;
}

int countChars(char* in, char c) {
    int l = strlen(in);
    int n = 0;
    for (int i = 0; i < l; ++i) {
        if (in[i] == c) {
            ++n;
        }
    }
    return n;
}

float getFloatFromStringSlice(char* begin, int length) {
    char* buf = malloc(length*sizeof(char)+1);
    memset(buf, 0, length*sizeof(char)+1);
    memcpy(buf, begin, length);

    float f = atof(buf);

    free(buf);

    return f;
}