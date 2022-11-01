#ifndef MATRIX_MULTIPLICATION_TEST_DEFINES_H
#define MATRIX_MULTIPLICATION_TEST_DEFINES_H

#include <stdio.h>
#include <string.h>

#include <serde.h>

#define TEST_SUCCESS 1
#define TEST_FAILURE 0

#define TEST_ASSERT(x, name) {\
    int res = x();\
    if (res == TEST_FAILURE) {\
        fprintf(stderr, "\033[91m  Test case %s failed with result: %d  \033[0m  \n", name, res);\
    } else {\
        fprintf(stderr, "\033[92m  Test case %s succeeded  \033[0m  \n", name);\
    }\
}

#define EXPECT_EQUAL(a, b, msg) {\
    if (a != b)  { \
        fprintf(stderr, msg); \
        return TEST_FAILURE; \
    } \
}

#define EXPECT_INTS_EQUAL(a, b, msg) {\
    if (a != b)  { \
        fprintf(stderr, msg); \
        fprintf(stderr, "expected: %d, got: %d\n", a, b); \
        return TEST_FAILURE; \
    } \
}

#define epsilon 0.005
#define EXPECT_FLOATS_EQUAL(a, b, msg) {\
    if ( ((a>=b) && (a-b) > epsilon) || ((a<b) && (b-a) > epsilon) ) {\
        fprintf(stderr, "error comparing floats: %s, expected: %f, got: %f\n", msg, a, b); \
        return TEST_FAILURE; \
    } \
}

#define EXPECT_ARRAYS_EQUAL(a, b, n, msg) {\
    for (int i = 0; i < n; ++i) { \
        if (a[i] != b[i]) { \
            fprintf(stderr, "array inequality at element %d: expected %f but got %f : %s", i, a[i], b[i], msg); \
            return TEST_FAILURE; \
        } \
    } \
}

#define EXPECT_STRINGS_EQUAL(a, b, msg) {\
    if ( strcmp(a, b) != 0) { \
        fprintf(stderr, msg); \
        fprintf(stderr, "expected:\n\t%s\ngot:\n\t%s\n", a, b); \
        return TEST_FAILURE; \
    } \
}

#endif