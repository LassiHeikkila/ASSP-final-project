#ifndef MATRIX_MULTIPLICATION_FIXED_POINT_H
#define MATRIX_MULTIPLICATION_FIXED_POINT_H

#include <inttypes.h>

typedef int16_t FixedPoint;

#define FIXED_POINT_SCALING_SHIFT 8
#define FIXED_POINT_SCALING_FACTOR (1 << FIXED_POINT_SCALING_SHIFT)

#define FIXED_POINT_MIN 0x8000
#define FIXED_POINT_MAX 0x7FFF

FixedPoint FloatToFixedPoint(float f);
float FixedPointToFloat(FixedPoint f);

FixedPoint FixedPointMultiply(FixedPoint a, FixedPoint b);
FixedPoint FixedPointAdd(FixedPoint a, FixedPoint b);

#endif