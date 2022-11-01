#include <float16.h>

// code is copied and adapted from the code provided in first laboratory exercise

Float16 uint32ToFloat16(uint32_t i) {
    register int s =  (i >> 16) & 0x00008000;                   // sign
    register int e = ((i >> 23) & 0x000000ff) - (127 - 15);     // exponent
    register int f =   i        & 0x007fffff;                   // fraction

    // need to handle NaNs and Inf?
    if (e <= 0) {
        if (e < -10) {
            if (s)                                              // handle -0.0
               return 0x8000;
            else
               return 0;
        }
        f = (f | 0x00800000) >> (1 - e);
        return s | (f >> 13);
    } else if (e == 0xff - (127 - 15)) {
        if (f == 0)                                             // Inf
            return s | 0x7c00;
        else {                                                  // NAN
            f >>= 13;
            return s | 0x7c00 | f | (f == 0);
        }
    } else {
        if (e > 30)                                             // Overflow
            return s | 0x7c00;
        return s | (e << 10) | (f >> 13);
    }
}

Float16 FloatToFloat16(float f) {
    // interpret the given float as just 32 bits
    union {
        float f;
        uint32_t i;
    } v;
    v.f = f;

    // convert 32 bits to Float16
    return uint32ToFloat16(v.i);
}

uint32_t float16ToUint32(Float16 y) {
    int s = (y >> 15) & 0x00000001;                            // sign
    int e = (y >> 10) & 0x0000001f;                            // exponent
    int f =  y        & 0x000003ff;                            // fraction

    // need to handle 7c00 INF and fc00 -INF?
    if (e == 0) {
        // need to handle +-0 case f==0 or f=0x8000?
        if (f == 0)                                            // Plus or minus zero
            return s << 31;
        else {                                                 // Denormalized number -- renormalize it
            while (!(f & 0x00000400)) {
                f <<= 1;
                e -=  1;
            }
            e += 1;
            f &= ~0x00000400;
        }
    } else if (e == 31) {
        if (f == 0)                                             // Inf
            return (s << 31) | 0x7f800000;
        else                                                    // NaN
            return (s << 31) | 0x7f800000 | (f << 13);
    }

    e = e + (127 - 15);
    f = f << 13;

    return ((s << 31) | (e << 23) | f);
}

float Float16ToFloat(Float16 f) {
    // convert Float16 to 32 bits of data and
    // interpret the 32 bits of data as float
    union { float f; uint32_t i; } v;
    v.i = float16ToUint32(f);
    return v.f;
}

Float16 Float16Multiply(Float16 a, Float16 b) {
    Float16 res;
    float af = Float16ToFloat(a);
    float bf = Float16ToFloat(b);
    float rf = af * bf;
    res = FloatToFloat16(rf);
    return res;
}

Float16 Float16Add(Float16 a, Float16 b) {
    Float16 res;
    float af = Float16ToFloat(a);
    float bf = Float16ToFloat(b);
    float rf = af + bf;
    res = FloatToFloat16(rf);
    return res;
}