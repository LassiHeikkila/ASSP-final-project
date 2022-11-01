#ifndef MATRIX_MULTIPLICATION_FLOAT16_H
#define MATRIX_MULTIPLICATION_FLOAT16_H

#include <inttypes.h>

// 1 bit sign
// 5 bit exponent with bias 15
// 10 bit significand
typedef uint16_t Float16;

Float16 FloatToFloat16(float f);
float Float16ToFloat(Float16 f);

Float16 Float16Multiply(Float16 a, Float16 b);
Float16 Float16Add(Float16 a, Float16 b);

#endif