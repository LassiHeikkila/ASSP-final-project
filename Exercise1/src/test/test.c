#include <string.h>

#include <test-defines.h>

#include <matrix-multiplication.h>
#include <serde.h>
#include <fixed-point.h>

int Test_ParseMatrix_A() {
    char* input = "[1.0]";
    float want[1] = {1.0};
    int wantRows = 1;
    int wantColumns = 1;

    float got[1];
    int gotRows, gotColumns = 0;

    int ret = unmarshalMatrix(input, Matlab, got, &gotRows, &gotColumns);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n")
    EXPECT_ARRAYS_EQUAL(want, got, 1, "expected matrix elements to equal\n")
    EXPECT_INTS_EQUAL(wantRows, gotRows, "expected rows to equal\n")
    EXPECT_INTS_EQUAL(wantColumns, gotColumns, "expected columns to equal\n")

    return TEST_SUCCESS;
}

int Test_ParseMatrix_B() {
    char* input = "[1.0 2.0; 3.0 4.0]";
    float want[4] = {
        1.0, 2.0, 
        3.0, 4.0
    };
    int wantRows = 2;
    int wantColumns = 2;

    float got[4];
    int gotRows, gotColumns = 0;

    int ret = unmarshalMatrix(input, Matlab, got, &gotRows, &gotColumns);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n")
    EXPECT_ARRAYS_EQUAL(want, got, 4, "expected matrix elements to equal\n")
    EXPECT_INTS_EQUAL(wantRows, gotRows, "expected rows to equal\n")
    EXPECT_INTS_EQUAL(wantColumns, gotColumns, "expected columns to equal\n")

    return TEST_SUCCESS;
}

int Test_ParseMatrix_C() {
    char* input = "[1.0 0.0 0.0; 0.0 1.0 0.0; 0.0 0.0 1.0]";
    float want[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    };
    int wantRows = 3;
    int wantColumns = 3;

    float got[9];
    int gotRows, gotColumns = 0;

    int ret = unmarshalMatrix(input, Matlab, got, &gotRows, &gotColumns);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n")
    EXPECT_ARRAYS_EQUAL(want, got, 9, "expected matrix elements to equal\n")
    EXPECT_INTS_EQUAL(wantRows, gotRows, "expected rows to equal\n")
    EXPECT_INTS_EQUAL(wantColumns, gotColumns, "expected columns to equal\n")

    return TEST_SUCCESS;
}

int Test_SerializeMatrix() {
    char buf[1024];
    memset(buf, 0, 1024);
    float input[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };

    char* expect = "[ 1.000000 0.000000 0.000000; 0.000000 1.000000 0.000000; 0.000000 0.000000 1.000000 ]";

    int ret = marshalMatrix(buf, Matlab, input, 3, 3);
    
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_STRINGS_EQUAL(expect, buf, "expected serialized matrix output to match expected form\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatricesSquareIdentity1x1_Float() {
    float A[1*1] = {1.0};
    float B[1*1] = {1.0};
    float R[1*1];

    float Expect[1*1] = {1.0};

    int ret = Matrix_Mul(A,B, R, 1, 1, 1, 1, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 1*1, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatricesSquareIdentity1x1_Fixed() {
    float A[1*1] = {1.0};
    float B[1*1] = {1.0};
    float R[1*1];

    float Expect[1*1] = {1.0};

    int ret = Matrix_Mul(A,B, R, 1, 1, 1, 1, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 1*1, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatricesSquareIdentity2x2_Float() {
    float A[2*2] = {
        1.0, 0.0, 
        0.0, 1.0
    };
    float B[2*2] = {
        1.0, 0.0, 
        0.0, 1.0
    };
    float R[2*2];

    float Expect[2*2] = {
        1.0, 0.0, 
        0.0, 1.0
    };

    int ret = Matrix_Mul(A,B, R, 2, 2, 2, 2, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 2*2, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatricesSquareIdentity2x2_Fixed() {
    float A[2*2] = {
        1.0, 0.0, 
        0.0, 1.0
    };
    float B[2*2] = {
        1.0, 0.0, 
        0.0, 1.0
    };
    float R[2*2];

    float Expect[2*2] = {
        1.0, 0.0, 
        0.0, 1.0
    };

    int ret = Matrix_Mul(A,B, R, 2, 2, 2, 2, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 2*2, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatricesSquareIdentity3x3_Float() {
    float A[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };
    float B[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };
    float R[3*3];

    float Expect[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };

    int ret = Matrix_Mul(A,B, R, 3, 3, 3, 3, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 3*3, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatricesSquareIdentity3x3_Fixed() {
    float A[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };
    float B[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };
    float R[3*3];

    float Expect[3*3] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };

    int ret = Matrix_Mul(A,B, R, 3, 3, 3, 3, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 3*3, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Float_A() {
    float A[4] = {
        1.0, 2.0, 
        3.0, 4.0
    };
    float B[4] = {
        5.0, 6.0, 
        7.0, 8.0
    };
    float R[4];

    float Expect[4] = {
        19.0, 22.0, 
        43.0, 50.0
    };
    
    int ret = Matrix_Mul(A, B, R, 2, 2, 2, 2, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 4, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Float_B() {
    float A[4*2] = {
        1.0, 2.0, 
        3.0, 4.0, 
        5.0, 6.0, 
        7.0, 8.0
    };
    float B[2*4] = {
        1.0, 2.0, 3.0, 4.0, 
        5.0, 6.0, 7.0, 8.0
    };
    float R[4*4];

    float Expect[4*4] = {
        11.0, 14.0, 17.0, 20.0,
        23.0, 30.0, 37.0, 44.0,
        35.0, 46.0, 57.0, 68.0,
        47.0, 62.0, 77.0, 92.0
    };
    
    int ret = Matrix_Mul(A, B, R, 4, 2, 2, 4, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 4*4, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Float_C() {
    float A[4*4] = {
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0
    };
    float B[4*4] = {
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0
    };
    float R[4*4];

    float Expect[4*4] = {
        10.0, 20.0, 30.0, 40.0,
        10.0, 20.0, 30.0, 40.0,
        10.0, 20.0, 30.0, 40.0,
        10.0, 20.0, 30.0, 40.0
    };
    
    int ret = Matrix_Mul(A, B, R, 4, 4, 4, 4, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 16, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Float_D() {
    float A[4*4] = {
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0,
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0
    };
    float B[4*4] = {
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0,
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0
    };
    float R[4*4];

    float Expect[4*4] = {
        10.0, -20.0, 30.0, -40.0,
        -10.0, 20.0, -30.0, 40.0,
        10.0, -20.0, 30.0, -40.0,
        -10.0, 20.0, -30.0, 40.0
    };
    
    int ret = Matrix_Mul(A, B, R, 4, 4, 4, 4, false);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 16, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Fixed_A() {
    float A[4] = {
        1.0, 2.0, 
        3.0, 4.0
    };
    float B[4] = {
        5.0, 6.0, 
        7.0, 8.0
    };
    float R[4];

    float Expect[4] = {
        19.0, 22.0, 
        43.0, 50.0
    };
    
    int ret = Matrix_Mul(A, B, R, 2, 2, 2, 2, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 4, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Fixed_B() {
    float A[4*2] = {
        1.0, 2.0, 
        3.0, 4.0, 
        5.0, 6.0, 
        7.0, 8.0
    };
    float B[2*4] = {
        1.0, 2.0, 3.0, 4.0, 
        5.0, 6.0, 7.0, 8.0
    };
    float R[4*4];

    float Expect[4*4] = {
        11.0, 14.0, 17.0, 20.0,
        23.0, 30.0, 37.0, 44.0,
        35.0, 46.0, 57.0, 68.0,
        47.0, 62.0, 77.0, 92.0
    };
    
    int ret = Matrix_Mul(A, B, R, 4, 2, 2, 4, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 4*4, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Fixed_C() {
    float A[4*4] = {
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0
    };
    float B[4*4] = {
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0,
        1.0, 2.0, 3.0, 4.0
    };
    float R[4*4];

    float Expect[4*4] = {
        10.0, 20.0, 30.0, 40.0,
        10.0, 20.0, 30.0, 40.0,
        10.0, 20.0, 30.0, 40.0,
        10.0, 20.0, 30.0, 40.0
    };
    
    int ret = Matrix_Mul(A, B, R, 4, 4, 4, 4, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 16, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_MultiplyMatrices_Fixed_D() {
    float A[4*4] = {
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0,
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0
    };
    float B[4*4] = {
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0,
        1.0, -2.0, 3.0, -4.0,
        -1.0, 2.0, -3.0, 4.0
    };
    float R[4*4];

    float Expect[4*4] = {
        10.0, -20.0, 30.0, -40.0,
        -10.0, 20.0, -30.0, 40.0,
        10.0, -20.0, 30.0, -40.0,
        -10.0, 20.0, -30.0, 40.0
    };
    
    int ret = Matrix_Mul(A, B, R, 4, 4, 4, 4, true);
    EXPECT_EQUAL(ret, 1, "expected ret to be 1\n");
    EXPECT_ARRAYS_EQUAL(Expect, R, 16, "expected matrix elements to equal\n");

    return TEST_SUCCESS;
}

int Test_FixedPointConversions() {
    EXPECT_INTS_EQUAL(1<<FIXED_POINT_SCALING_SHIFT, FloatToFixedPoint(1.0), "case 1.0 to fixed point\n");
    EXPECT_INTS_EQUAL(2<<FIXED_POINT_SCALING_SHIFT, FloatToFixedPoint(2.0), "case 2.0 to fixed point\n");
    EXPECT_INTS_EQUAL(1503, FloatToFixedPoint(5.87), "case 5.87 to fixed point\n");
    EXPECT_INTS_EQUAL(-804, FloatToFixedPoint(-3.14), "case -3.14 to fixed point\n");
    EXPECT_INTS_EQUAL(2534, FloatToFixedPoint(9.9), "case 9.9 to fixed point\n");

    EXPECT_FLOATS_EQUAL(1.0, FixedPointToFloat(1 << FIXED_POINT_SCALING_SHIFT), "case 1.0 from fixed point\n");
    EXPECT_FLOATS_EQUAL(2.0, FixedPointToFloat(2 << FIXED_POINT_SCALING_SHIFT), "case 2.0 from fixed point\n");
    EXPECT_FLOATS_EQUAL(5.87, FixedPointToFloat(1503), "case 5.87 from fixed point\n");
    EXPECT_FLOATS_EQUAL(-3.14, FixedPointToFloat(-804), "case -3.14 from fixed point\n");
    EXPECT_FLOATS_EQUAL(9.9, FixedPointToFloat(2534), "case 9.9 from fixed point\n");
    return TEST_SUCCESS;
}

int Test_FixedPointAddition() {
    EXPECT_INTS_EQUAL(FloatToFixedPoint(5.0), FixedPointAdd(FloatToFixedPoint(2.0), FloatToFixedPoint(3.0)), "case 2.0 + 3.0\n");
    EXPECT_INTS_EQUAL(FloatToFixedPoint(0.0), FixedPointAdd(FloatToFixedPoint(2.0), FloatToFixedPoint(-2.0)), "case 2.0 - 2.0\n");
    EXPECT_INTS_EQUAL(FloatToFixedPoint(-85.0), FixedPointAdd(FloatToFixedPoint(-35.0), FloatToFixedPoint(-50.0)), "case -35.0 - 50.0\n");

    return TEST_SUCCESS;
}

int Test_FixedPointMultiplication() {
    EXPECT_INTS_EQUAL(FloatToFixedPoint(10.0), FixedPointMultiply(FloatToFixedPoint(2.0), FloatToFixedPoint(5.0)), "case 2.0 * 5.0\n");
    EXPECT_INTS_EQUAL(FloatToFixedPoint(1.0), FixedPointMultiply(FloatToFixedPoint(-1.0), FloatToFixedPoint(-1.0)), "case -1.0 * -1.0\n");
    EXPECT_INTS_EQUAL(FloatToFixedPoint(100.0), FixedPointMultiply(FloatToFixedPoint(20.0), FloatToFixedPoint(5.0)), "case 20.0 * 5.0\n");
    EXPECT_INTS_EQUAL(FloatToFixedPoint(-35.0), FixedPointMultiply(FloatToFixedPoint(-17.5), FloatToFixedPoint(2.0)), "case -17.5 * 2.0\n");

    return TEST_SUCCESS;
}

int Test_FixedPointRange() {
    const float fixedPointMinRequirement = -100.0;
    const float fixedPointMaxRequirement = 100.0;

    float min = FixedPointToFloat(FIXED_POINT_MIN);
    float max = FixedPointToFloat(FIXED_POINT_MAX);

    EXPECT_EQUAL(min < fixedPointMinRequirement, true, "expected minimum supported fixed point number to be smaller than the requirement\n");
    EXPECT_EQUAL(max > fixedPointMaxRequirement, true, "expected maximum supported fixed point number to be greater than the requirement\n");

    return TEST_SUCCESS;
}

int main() {
    TEST_ASSERT(Test_ParseMatrix_A, "ParseMatrix_A");
    TEST_ASSERT(Test_ParseMatrix_B, "ParseMatrix_B");
    TEST_ASSERT(Test_ParseMatrix_C, "ParseMatrix_C");
    TEST_ASSERT(Test_SerializeMatrix, "SerializeMatrix");
    TEST_ASSERT(Test_MultiplyMatricesSquareIdentity1x1_Float, "MultiplyMatricesSquareIdentity1x1_Float");
    TEST_ASSERT(Test_MultiplyMatricesSquareIdentity2x2_Float, "MultiplyMatricesSquareIdentity2x2_Float");
    TEST_ASSERT(Test_MultiplyMatricesSquareIdentity3x3_Float, "MultiplyMatricesSquareIdentity3x3_Float");
    TEST_ASSERT(Test_MultiplyMatricesSquareIdentity1x1_Fixed, "MultiplyMatricesSquareIdentity1x1_Fixed");
    TEST_ASSERT(Test_MultiplyMatricesSquareIdentity2x2_Fixed, "MultiplyMatricesSquareIdentity2x2_Fixed");
    TEST_ASSERT(Test_MultiplyMatricesSquareIdentity3x3_Fixed, "MultiplyMatricesSquareIdentity3x3_Fixed");
    TEST_ASSERT(Test_MultiplyMatrices_Float_A, "MultiplyMatrices_Float_A");
    TEST_ASSERT(Test_MultiplyMatrices_Float_B, "MultiplyMatrices_Float_B");
    TEST_ASSERT(Test_MultiplyMatrices_Float_C, "MultiplyMatrices_Float_C");
    TEST_ASSERT(Test_MultiplyMatrices_Float_D, "MultiplyMatrices_Float_D");
    TEST_ASSERT(Test_MultiplyMatrices_Fixed_A, "MultiplyMatrices_Fixed_A");
    TEST_ASSERT(Test_MultiplyMatrices_Fixed_B, "MultiplyMatrices_Fixed_B");
    TEST_ASSERT(Test_MultiplyMatrices_Fixed_C, "MultiplyMatrices_Fixed_C");
    TEST_ASSERT(Test_MultiplyMatrices_Fixed_D, "MultiplyMatrices_Fixed_D");
    TEST_ASSERT(Test_FixedPointConversions, "FixedPointConversions");
    TEST_ASSERT(Test_FixedPointAddition, "FixedPointAddition");
    TEST_ASSERT(Test_FixedPointMultiplication, "FixedPointMultiplication");
    TEST_ASSERT(Test_FixedPointRange, "FixedPointRange");
}