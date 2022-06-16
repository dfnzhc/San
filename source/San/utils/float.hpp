//
// Created by 秋鱼 on 2022/6/16.
//

#pragma once

#include "defines.hpp"

#ifdef SAN_USE_GPU
#include <cuda_fp16.h>
#endif

namespace San {

#ifdef SAN_USE_GPU

#define DoubleOneMinusEpsilon 0x1.fffffffffffffp-1
#define FloatOneMinusEpsilon float(0x1.fffffep-1)

#ifdef SAN_FLOAT_AS_DOUBLE
#define OneMinusEpsilon DoubleOneMinusEpsilon
#else
#define OneMinusEpsilon FloatOneMinusEpsilon
#endif

#define Infinity std::numeric_limits<Float>::infinity()
#define MachineEpsilon std::numeric_limits<Float>::epsilon() * 0.5f

#else

// Floating-point Constants
static constexpr Float Infinity = std::numeric_limits<Float>::infinity();

static constexpr Float MachineEpsilon = static_cast<Float>(std::numeric_limits<Float>::epsilon() * 0.5);

static constexpr double DoubleOneMinusEpsilon = 0x1.fffffffffffffp-1;
static constexpr float FloatOneMinusEpsilon = 0x1.fffffep-1;
#ifdef SAN_FLOAT_AS_DOUBLE
static constexpr double OneMinusEpsilon = DoubleOneMinusEpsilon;
#else
static constexpr float OneMinusEpsilon = FloatOneMinusEpsilon;
#endif

#endif  // SAN_USE_GPU

template<typename T>
concept FloatType = std::is_floating_point_v<T>;
template<typename T>
concept IntegerType = std::is_integral_v<T>;

// Floating-point Inline Functions
template<FloatType T>
SAN_CPU_GPU inline bool IsNaN(T v)
{
#ifdef SAN_USE_GPU
    return isnan(v);
#else
    return std::isnan(v);
#endif
}

template<IntegerType T>
SAN_CPU_GPU inline bool IsNaN(T v)
{
    return false;
}

template<FloatType T>
SAN_CPU_GPU inline bool IsInf(
    T v)
{
#ifdef SAN_USE_GPU
    return isinf(v);
#else
    return std::isinf(v);
#endif
}

template<IntegerType T>
SAN_CPU_GPU inline bool IsInf(T v)
{
    return false;
}

template<FloatType T>
SAN_CPU_GPU inline bool IsFinite(T v)
{
#ifdef SAN_USE_GPU
    return isfinite(v);
#else
    return std::isfinite(v);
#endif
}

template<IntegerType T>
SAN_CPU_GPU inline bool IsFinite(T v)
{
    return true;
}

SAN_CPU_GPU inline float FMA(float a, float b, float c)
{
    return std::fma(a, b, c);
}

SAN_CPU_GPU
inline double FMA(double a, double b, double c)
{
    return std::fma(a, b, c);
}
inline long double FMA(long double a, long double b, long double c)
{
    return std::fma(a, b, c);
}

SAN_CPU_GPU
inline uint32_t FloatToBits(float f)
{
#ifdef SAN_USE_GPU
    return __float_as_uint(f);
#else
    return std::bit_cast<uint32_t>(f);
#endif
}

SAN_CPU_GPU
inline float BitsToFloat(uint32_t ui)
{
#ifdef SAN_USE_GPU
    return __uint_as_float(ui);
#else
    return std::bit_cast<float>(ui);
#endif
}

SAN_CPU_GPU
inline int Exponent(float v)
{
    return (FloatToBits(v) >> 23) - 127;
}

SAN_CPU_GPU
inline int Significand(float v)
{
    return FloatToBits(v) & ((1 << 23) - 1);
}

SAN_CPU_GPU
inline uint32_t SignBit(float v)
{
    return FloatToBits(v) & 0x80000000;
}

SAN_CPU_GPU
inline uint64_t FloatToBits(double f)
{
#ifdef SAN_USE_GPU
    return __double_as_longlong(f);
#else
    return std::bit_cast<uint64_t>(f);
#endif
}

SAN_CPU_GPU
inline double BitsToFloat(uint64_t ui)
{
#ifdef SAN_USE_GPU
    return __longlong_as_double(ui);
#else
    return std::bit_cast<double>(ui);
#endif
}

SAN_CPU_GPU
inline float NextFloatUp(float v)
{
    // Handle infinity and negative zero for _NextFloatUp()_
    if (IsInf(v) && v > 0.f)
        return v;
    if (v == -0.f)
        v = 0.f;

    // Advance _v_ to next higher float
    uint32_t ui = FloatToBits(v);
    if (v >= 0)
        ++ui;
    else
        --ui;
    return BitsToFloat(ui);
}

SAN_CPU_GPU
inline float NextFloatDown(float v)
{
    // Handle infinity and positive zero for _NextFloatDown()_
    if (IsInf(v) && v < 0.)
        return v;
    if (v == 0.f)
        v = -0.f;
    
    uint32_t ui = FloatToBits(v);
    if (v > 0)
        --ui;
    else
        ++ui;
    return BitsToFloat(ui);
}

inline constexpr Float gamma(int n)
{
    return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
}

inline SAN_CPU_GPU Float AddRoundUp(Float a, Float b)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __dadd_ru(a, b);
#else
    return __fadd_ru(a, b);
#endif
#else  // GPU
    return NextFloatUp(a + b);
#endif
}
inline SAN_CPU_GPU Float AddRoundDown(Float a, Float b)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __dadd_rd(a, b);
#else
    return __fadd_rd(a, b);
#endif
#else  // GPU
    return NextFloatDown(a + b);
#endif
}

inline SAN_CPU_GPU Float SubRoundUp(Float a, Float b)
{
    return AddRoundUp(a, -b);
}
inline SAN_CPU_GPU Float SubRoundDown(Float a, Float b)
{
    return AddRoundDown(a, -b);
}

inline SAN_CPU_GPU Float MulRoundUp(Float a, Float b)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __dmul_ru(a, b);
#else
    return __fmul_ru(a, b);
#endif
#else  // GPU
    return NextFloatUp(a * b);
#endif
}

inline SAN_CPU_GPU Float MulRoundDown(Float a, Float b)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __dmul_rd(a, b);
#else
    return __fmul_rd(a, b);
#endif
#else  // GPU
    return NextFloatDown(a * b);
#endif
}

inline SAN_CPU_GPU Float DivRoundUp(Float a, Float b)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __ddiv_ru(a, b);
#else
    return __fdiv_ru(a, b);
#endif
#else  // GPU
    return NextFloatUp(a / b);
#endif
}

inline SAN_CPU_GPU Float DivRoundDown(Float a, Float b)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __ddiv_rd(a, b);
#else
    return __fdiv_rd(a, b);
#endif
#else  // GPU
    return NextFloatDown(a / b);
#endif
}

inline SAN_CPU_GPU Float SqrtRoundUp(Float a)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __dsqrt_ru(a);
#else
    return __fsqrt_ru(a);
#endif
#else  // GPU
    return NextFloatUp(std::sqrt(a));
#endif
}

inline SAN_CPU_GPU Float SqrtRoundDown(Float a)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __dsqrt_rd(a);
#else
    return __fsqrt_rd(a);
#endif
#else  // GPU
    return std::max<Float>(0, NextFloatDown(std::sqrt(a)));
#endif
}

inline SAN_CPU_GPU Float FMARoundUp(Float a, Float b, Float c)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __fma_ru(a, b, c);  // 使用单精度算法
#else
    return __fma_ru(a, b, c);
#endif
#else  // GPU
    return NextFloatUp(FMA(a, b, c));
#endif
}

inline SAN_CPU_GPU Float FMARoundDown(Float a, Float b, Float c)
{
#ifdef SAN_USE_GPU
#ifdef SAN_FLOAT_AS_DOUBLE
    return __fma_rd(a, b, c);  // 使用单精度算法
#else
    return __fma_rd(a, b, c);
#endif
#else  // GPU
    return NextFloatDown(FMA(a, b, c));
#endif
}

SAN_CPU_GPU
inline double NextFloatUp(double v)
{
    if (IsInf(v) && v > 0.)
        return v;
    if (v == -0.f)
        v = 0.f;
    uint64_t ui = FloatToBits(v);
    if (v >= 0.)
        ++ui;
    else
        --ui;
    return BitsToFloat(ui);
}

SAN_CPU_GPU
inline double NextFloatDown(double v)
{
    if (IsInf(v) && v < 0.)
        return v;
    if (v == 0.f)
        v = -0.f;
    uint64_t ui = FloatToBits(v);
    if (v > 0.)
        --ui;
    else
        ++ui;
    return BitsToFloat(ui);
}

SAN_CPU_GPU
inline int Exponent(double d)
{
    return (FloatToBits(d) >> 52) - 1023;
}

SAN_CPU_GPU
inline uint64_t Significand(double d)
{
    return FloatToBits(d) & ((1ull << 52) - 1);
}

SAN_CPU_GPU
inline uint64_t SignBit(double v)
{
    return FloatToBits(v) & 0x8000000000000000;
}

SAN_CPU_GPU
inline double FlipSign(double a, double b)
{
    return BitsToFloat(FloatToBits(a) ^ SignBit(b));
}

} // San