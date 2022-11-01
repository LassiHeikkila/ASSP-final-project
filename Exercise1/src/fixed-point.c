#include <math.h>

#include <fixed-point.h>

FixedPoint FloatToFixedPoint(float f) {
    return (FixedPoint)(round(f*(FIXED_POINT_SCALING_FACTOR)));
}

float FixedPointToFloat(FixedPoint f) {
    return (float)f / (float)(FIXED_POINT_SCALING_FACTOR);
}

FixedPoint FixedPointMultiply(FixedPoint a, FixedPoint b) {
    // intermediate calculation must use longer type
    int32_t res = a*b;
    return (FixedPoint)(res>>FIXED_POINT_SCALING_SHIFT);
}

FixedPoint FixedPointAdd(FixedPoint a, FixedPoint b) {
    return a + b;
}