//
// Created by 秋鱼 on 2022/6/14.
//

#pragma once

#include "check.hpp"
#include "float.hpp"

namespace San {

#ifdef SAN_USE_GPU

#define ShadowEpsilon   0.0001f
#define Pi              Float(3.14159265358979323846)
#define InvPi           Float(0.31830988618379067154)
#define Inv2Pi          Float(0.15915494309189533577)
#define Inv4Pi          Float(0.07957747154594766788)
#define PiOver2         Float(1.57079632679489661923)
#define PiOver4         Float(0.78539816339744830961)
#define Sqrt2           Float(1.41421356237309504880)

#else

// Mathematical Constants
constexpr Float ShadowEpsilon = static_cast<Float>(0.0001f);

constexpr Float Pi = static_cast<Float>(3.14159265358979323846);
constexpr Float InvPi = static_cast<Float>(0.31830988618379067154);
constexpr Float Inv2Pi = static_cast<Float>(0.15915494309189533577);
constexpr Float Inv4Pi = static_cast<Float>(0.07957747154594766788);
constexpr Float PiOver2 = static_cast<Float>(1.57079632679489661923);
constexpr Float PiOver4 = static_cast<Float>(0.78539816339744830961);
constexpr Float Sqrt2 = static_cast<Float>(1.41421356237309504880);

#endif

SAN_CPU_GPU
inline uint32_t ReverseBits32(uint32_t n)
{
#ifdef SAN_USE_GPU
    return __brev(n);
#else
    n = (n << 16) | (n >> 16);
    n = ((n & 0x00ff00ff) << 8) | ((n & 0xff00ff00) >> 8);
    n = ((n & 0x0f0f0f0f) << 4) | ((n & 0xf0f0f0f0) >> 4);
    n = ((n & 0x33333333) << 2) | ((n & 0xcccccccc) >> 2);
    n = ((n & 0x55555555) << 1) | ((n & 0xaaaaaaaa) >> 1);
    return n;
#endif
}

SAN_CPU_GPU
inline uint64_t ReverseBits64(uint64_t n)
{
#ifdef SAN_USE_GPU
    return __brevll(n);
#else
    uint64_t n0 = ReverseBits32((uint32_t) n);
    uint64_t n1 = ReverseBits32((uint32_t) (n >> 32));
    return (n0 << 32) | n1;
#endif
}

template<typename T, typename U, typename V>
SAN_CPU_GPU
inline constexpr T Clamp(T val, U low, V high)
{
    if (val < low)
        return T(low);
    else if (val > high)
        return T(high);
    else
        return val;
}

// http://www.plunk.org/~hatch/rightway.html
SAN_CPU_GPU
inline Float SinXOverX(Float x)
{
    if (1 + x * x == 1)
        return 1;
    return std::sin(x) / x;
}

SAN_CPU_GPU
inline Float Sinc(Float x)
{
    return SinXOverX(Pi * x);
}

SAN_CPU_GPU inline Float
WindowedSinc(Float x, Float radius, Float tau)
{
    if (std::abs(x) > radius)
        return 0;
    return
        Sinc(x) * Sinc(x / tau);
}

SAN_CPU_GPU inline float SafeASin(float x)
{
    DCHECK(x >= -1.0001 && x <= 1.0001);
    return std::asin(Clamp(x, -1, 1));
}

SAN_CPU_GPU inline float SafeACos(float x)
{
    DCHECK(x >= -1.0001 && x <= 1.0001);
    return std::acos(Clamp(x, -1, 1));
}

SAN_CPU_GPU
inline double SafeASin(double x)
{
    DCHECK(x >= -1.0001 && x <= 1.0001);
    return std::asin(Clamp(x, -1, 1));
}

SAN_CPU_GPU
inline double SafeACos(double x)
{
    DCHECK(x >= -1.0001 && x <= 1.0001);
    return std::acos(Clamp(x, -1, 1));
}

template<typename T>
SAN_CPU_GPU inline T Mod(T a, T b)
{
    T result = a - (a / b) * b;
    return (T) ((result < 0) ? result + b : result);
}

template<>
SAN_CPU_GPU inline Float Mod(Float a, Float b)
{
    return std::fmod(a, b);
}

SAN_CPU_GPU inline Float Radians(Float deg)
{
    return (Pi / 180) * deg;
}
SAN_CPU_GPU inline Float Degrees(Float rad)
{
    return (180 / Pi) * rad;
}

SAN_CPU_GPU inline Float SmoothStep(Float x, Float a, Float b)
{
    if (a == b)
        return static_cast<Float>((x < a) ? 0 : 1);
    DCHECK_LT(a, b);
    Float t = Clamp((x - a) / (b - a), 0, 1);
    return t * t * (3 - 2 * t);
}

SAN_CPU_GPU inline float SafeSqrt(float x)
{
    DCHECK_GE(x, -1e-3f);  // not too negative
    return std::sqrt(std::max(0.f, x));
}

SAN_CPU_GPU
inline double SafeSqrt(double x)
{
    DCHECK_GE(x, -1e-3);  // not too negative
    return std::sqrt(std::max(0., x));
}

template<typename T>
SAN_CPU_GPU inline constexpr T Sqr(T v)
{
    return v * v;
}

// Would be nice to allow Float to be a template type here, but it is tricky:
// https://stackoverflow.com/questions/5101516/why-function-template-cannot-be-partially-specialized
template<int n>
SAN_CPU_GPU inline constexpr float Pow(float v)
{
    if constexpr (n < 0)
        return 1 / Pow<-n>(v);
    float n2 = Pow<n / 2>(v);
    return n2 * n2 * Pow<n & 1>(v);
}

template<>
SAN_CPU_GPU inline constexpr float Pow<1>(float v)
{
    return v;
}
template<>
SAN_CPU_GPU inline constexpr float Pow<0>(float v)
{
    return 1;
}

template<int n>
SAN_CPU_GPU inline constexpr double Pow(double v)
{
    if constexpr (n < 0)
        return 1 / Pow<-n>(v);
    double n2 = Pow<n / 2>(v);
    return n2 * n2 * Pow<n & 1>(v);
}

template<>
SAN_CPU_GPU inline constexpr double Pow<1>(double v)
{
    return v;
}

template<>
SAN_CPU_GPU inline constexpr double Pow<0>(double v)
{
    return 1;
}

template<typename Float, typename C>
SAN_CPU_GPU inline constexpr Float EvaluatePolynomial(Float t, C c)
{
    return c;
}

template<typename Float, typename C, typename... Args>
SAN_CPU_GPU inline constexpr Float EvaluatePolynomial(Float t, C c, Args... cRemaining)
{
    return FMA(t, EvaluatePolynomial(t, cRemaining...), c);
}

SAN_CPU_GPU inline Float Log2(Float x)
{
    const auto invLog2 = static_cast<Float>(1.442695040888963387004650940071);
    return std::log(x) * invLog2;
}

SAN_CPU_GPU inline int Log2Int(float v)
{
    DCHECK_GT(v, 0);
    if (v < 1)
        return -Log2Int(1 / v);
    // https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog
    // (With an additional check of the significant to get round-to-nearest
    // rather than round down.)
    // midsignif = Significand(std::pow(2., 1.5))
    // i.e. grab the significand of a value halfway between two exponents,
    // in log space.
    const uint32_t midsignif = 0b00000000001101010000010011110011;
    return Exponent(v) + ((Significand(v) >= midsignif) ? 1 : 0);
}

SAN_CPU_GPU
inline int Log2Int(double v)
{
    DCHECK_GT(v, 0);
    if (v < 1)
        return -Log2Int(1 / v);
    // https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog
    // (With an additional check of the significant to get round-to-nearest
    // rather than round down.)
    // midsignif = Significand(std::pow(2., 1.5))
    // i.e. grab the significand of a value halfway between two exponents,
    // in log space.
    const uint64_t midsignif = 0b110101000001001111001100110011111110011101111001101;
    return Exponent(v) + ((Significand(v) >= midsignif) ? 1 : 0);
}

// https://stackoverflow.com/a/10792321
SAN_CPU_GPU inline float FastExp(float x)
{
#ifdef SAN_USE_GPU
    return __expf(x);
#else
    // Compute $x'$ such that $\roman{e}^x = 2^{x'}$
    float xp = x * 1.442695041f;

    // Find integer and fractional components of $x'$
    float fxp = std::floor(xp), f = xp - fxp;
    int i = (int) fxp;

    // Evaluate polynomial approximation of $2^f$
    float twoToF = EvaluatePolynomial(f, 1.f, 0.695556856f, 0.226173572f, 0.0781455737f);

    // Scale $2^f$ by $2^i$ and return final result
    int exponent = Exponent(twoToF) + i;
    if (exponent < -126)
        return 0;
    if (exponent > 127)
        return Infinity;
    uint32_t bits = FloatToBits(twoToF);
    bits &= 0b10000000011111111111111111111111u;
    bits |= (exponent + 127) << 23;
    return BitsToFloat(bits);

#endif
}

SAN_CPU_GPU inline Float Gaussian(Float x, Float mu = 0, Float sigma = 1)
{
    return 1 / std::sqrt(2 * Pi * sigma * sigma) * FastExp(-Sqr(x - mu) / (2 * sigma * sigma));
}

SAN_CPU_GPU inline Float GaussianIntegral(Float x0, Float x1, Float mu = 0,
                                          Float sigma = 1)
{
    DCHECK_GT(sigma, 0);
    Float sigmaRoot2 = sigma * Float(1.414213562373095);
    return 0.5f * (std::erf((mu - x0) / sigmaRoot2) - std::erf((mu - x1) / sigmaRoot2));
}

template<typename T>
inline T AlignUp(T val, T alignment)
{
    return (val + alignment - static_cast<T>(1)) & ~(alignment - static_cast<T>(1));
}

template<typename T>
SAN_CPU_GPU inline constexpr bool IsPowerOf2(T v)
{
    return v && !(v & (v - 1));
}

SAN_CPU_GPU
inline constexpr int32_t RoundUpPow2(int32_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return v + 1;
}

SAN_CPU_GPU
inline constexpr int64_t RoundUpPow2(int64_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    return v + 1;
}

template <typename Ta, typename Tb, typename Tc, typename Td>
SAN_CPU_GPU inline auto DifferenceOfProducts(Ta a, Tb b, Tc c, Td d) {
    auto cd = c * d;
    auto differenceOfProducts = FMA(a, b, -cd);
    auto error = FMA(-c, d, cd);
    return differenceOfProducts + error;
}

template <typename Ta, typename Tb, typename Tc, typename Td>
SAN_CPU_GPU inline auto SumOfProducts(Ta a, Tb b, Tc c, Td d) {
    auto cd = c * d;
    auto sumOfProducts = FMA(a, b, cd);
    auto error = FMA(c, d, -cd);
    return sumOfProducts + error;
}

// CompensatedFloat Definition
struct CompensatedFloat {
  public:
    // CompensatedFloat Public Methods
    SAN_CPU_GPU
    CompensatedFloat(Float v, Float err = 0) : v(v), err(err) {}
    SAN_CPU_GPU
    explicit operator float() const { return v + err; }
    SAN_CPU_GPU
    explicit operator double() const { return double(v) + double(err); }
    std::string ToString() const;

    Float v, err;
};

SAN_CPU_GPU inline CompensatedFloat TwoProd(Float a, Float b) {
    Float ab = a * b;
    return {ab, FMA(a, b, -ab)};
}

SAN_CPU_GPU inline CompensatedFloat TwoSum(Float a, Float b) {
    Float s = a + b, delta = s - a;
    return {s, (a - (s - delta)) + (b - delta)};
}

// InnerProduct Helper Functions
template <typename Float>
SAN_CPU_GPU inline CompensatedFloat InnerProduct(Float a, Float b) {
    return TwoProd(a, b);
}

// Accurate dot products with FMA: Graillat et al.,
// http://rnc7.loria.fr/louvet_poster.pdf
//
// Accurate summation, dot product and polynomial evaluation in complex
// floating point arithmetic, Graillat and Menissier-Morain.
template <typename Float, typename... T>
SAN_CPU_GPU inline CompensatedFloat InnerProduct(Float a, Float b, T... terms) {
    CompensatedFloat ab = TwoProd(a, b);
    CompensatedFloat tp = InnerProduct(terms...);
    CompensatedFloat sum = TwoSum(ab.v, tp.v);
    return {sum.v, ab.err + (tp.err + sum.err)};
}

// Interval Definition
class Interval
{
public:
    // Interval Public Methods
    Interval() = default;
    SAN_CPU_GPU
    explicit Interval(Float v) : low(v), high(v) {}
    SAN_CPU_GPU constexpr Interval(Float low, Float high)
        : low(std::min(low, high)), high(std::max(low, high)) {}

    SAN_CPU_GPU
    static Interval FromValueAndError(Float v, Float err)
    {
        Interval i;
        if (err == 0)
            i.low = i.high = v;
        else {
            i.low = SubRoundDown(v, err);
            i.high = AddRoundUp(v, err);
        }
        return i;
    }

    SAN_CPU_GPU
    Interval& operator=(Float v)
    {
        low = high = v;
        return *this;
    }

    SAN_CPU_GPU
    Float UpperBound() const { return high; }
    SAN_CPU_GPU
    Float LowerBound() const { return low; }
    SAN_CPU_GPU
    Float Midpoint() const { return (low + high) / 2; }
    SAN_CPU_GPU
    Float Width() const { return high - low; }

    SAN_CPU_GPU
    Float operator[](int i) const
    {
        DCHECK(i == 0 || i == 1);
        return (i == 0) ? low : high;
    }

    SAN_CPU_GPU
    explicit operator Float() const { return Midpoint(); }

    SAN_CPU_GPU
    bool Exactly(Float v) const { return low == v && high == v; }

    SAN_CPU_GPU
    bool operator==(Float v) const { return Exactly(v); }

    SAN_CPU_GPU
    Interval operator-() const { return {-high, -low}; }

    SAN_CPU_GPU
    Interval operator+(Interval i) const
    {
        return {AddRoundDown(low, i.low), AddRoundUp(high, i.high)};
    }

    SAN_CPU_GPU
    Interval operator-(Interval i) const
    {
        return {SubRoundDown(low, i.high), SubRoundUp(high, i.low)};
    }

    SAN_CPU_GPU
    Interval operator*(Interval i) const
    {
        Float lp[4] = {MulRoundDown(low, i.low), MulRoundDown(high, i.low),
                       MulRoundDown(low, i.high), MulRoundDown(high, i.high)};
        Float hp[4] = {MulRoundUp(low, i.low), MulRoundUp(high, i.low),
                       MulRoundUp(low, i.high), MulRoundUp(high, i.high)};
        return {std::min({lp[0], lp[1], lp[2], lp[3]}),
                std::max({hp[0], hp[1], hp[2], hp[3]})};
    }

    SAN_CPU_GPU
    Interval operator/(Interval i) const;

    SAN_CPU_GPU bool operator==(Interval i) const
    {
        return low == i.low && high == i.high;
    }

    SAN_CPU_GPU
    bool operator!=(Float f) const { return f < low || f > high; }

    std::string ToString() const;

    SAN_CPU_GPU Interval& operator+=(Interval i)
    {
        *this = Interval(*this + i);
        return *this;
    }
    SAN_CPU_GPU Interval& operator-=(Interval i)
    {
        *this = Interval(*this - i);
        return *this;
    }
    SAN_CPU_GPU Interval& operator*=(Interval i)
    {
        *this = Interval(*this * i);
        return *this;
    }
    SAN_CPU_GPU Interval& operator/=(Interval i)
    {
        *this = Interval(*this / i);
        return *this;
    }
    SAN_CPU_GPU
    Interval& operator+=(Float f) { return *this += Interval(f); }
    SAN_CPU_GPU
    Interval& operator-=(Float f) { return *this -= Interval(f); }
    SAN_CPU_GPU
    Interval& operator*=(Float f)
    {
        if (f > 0)
            *this = Interval(MulRoundDown(f, low), MulRoundUp(f, high));
        else
            *this = Interval(MulRoundDown(f, high), MulRoundUp(f, low));
        return *this;
    }
    SAN_CPU_GPU
    Interval& operator/=(Float f)
    {
        if (f > 0)
            *this = Interval(DivRoundDown(low, f), DivRoundUp(high, f));
        else
            *this = Interval(DivRoundDown(high, f), DivRoundUp(low, f));
        return *this;
    }

#ifndef PBRT_IS_GPU_CODE
    static const Interval Pi;
#endif

private:
    // Interval Private Members
    Float low, high;
};

// Interval Inline Functions
SAN_CPU_GPU inline bool InRange(Float v, Interval i)
{
    return v >= i.LowerBound() && v <= i.UpperBound();
}
SAN_CPU_GPU inline bool InRange(Interval a, Interval b)
{
    return a.LowerBound() <= b.UpperBound() && a.UpperBound() >= b.LowerBound();
}

inline Interval Interval::operator/(Interval i) const
{
    if (InRange(0, i))
        // The interval we're dividing by straddles zero, so just
        // return an interval of everything.
        return {-Infinity, Infinity};

    Float lowQuot[4] = {DivRoundDown(low, i.low), DivRoundDown(high, i.low),
                        DivRoundDown(low, i.high), DivRoundDown(high, i.high)};
    Float highQuot[4] = {DivRoundUp(low, i.low), DivRoundUp(high, i.low),
                         DivRoundUp(low, i.high), DivRoundUp(high, i.high)};
    return {std::min({lowQuot[0], lowQuot[1], lowQuot[2], lowQuot[3]}),
            std::max({highQuot[0], highQuot[1], highQuot[2], highQuot[3]})};
}

SAN_CPU_GPU inline Interval Sqr(Interval i)
{
    Float alow = std::abs(i.LowerBound()), ahigh = std::abs(i.UpperBound());
    if (alow > ahigh)
        std::swap(alow, ahigh);
    if (InRange(0, i))
        return {0, MulRoundUp(ahigh, ahigh)};
    return {MulRoundDown(alow, alow), MulRoundUp(ahigh, ahigh)};
}

SAN_CPU_GPU inline Interval MulPow2(Float s, Interval i);
SAN_CPU_GPU inline Interval MulPow2(Interval i, Float s);

SAN_CPU_GPU inline Interval operator+(Float f, Interval i)
{
    return Interval(f) + i;
}

SAN_CPU_GPU inline Interval operator-(Float f, Interval i)
{
    return Interval(f) - i;
}

SAN_CPU_GPU inline Interval operator*(Float f, Interval i)
{
    if (f > 0)
        return {MulRoundDown(f, i.LowerBound()), MulRoundUp(f, i.UpperBound())};
    else
        return {MulRoundDown(f, i.UpperBound()), MulRoundUp(f, i.LowerBound())};
}

SAN_CPU_GPU inline Interval operator/(Float f, Interval i)
{
    if (InRange(0, i))
// The interval we're dividing by straddles zero, so just
// return an interval of everything.
        return {-Infinity, Infinity};

    if (f > 0)
        return {DivRoundDown(f, i.UpperBound()), DivRoundUp(f, i.LowerBound())};
    else
        return {DivRoundDown(f, i.LowerBound()), DivRoundUp(f, i.UpperBound())};
}

SAN_CPU_GPU inline Interval operator+(Interval i, Float f)
{
    return i + Interval(f);
}

SAN_CPU_GPU inline Interval operator-(Interval i, Float f)
{
    return i - Interval(f);
}

SAN_CPU_GPU inline Interval operator*(Interval i, Float f)
{
    if (f > 0)
        return {MulRoundDown(f, i.LowerBound()), MulRoundUp(f, i.UpperBound())};
    else
        return {MulRoundDown(f, i.UpperBound()), MulRoundUp(f, i.LowerBound())};
}

SAN_CPU_GPU inline Interval operator/(Interval i, Float f)
{
    if (f == 0)
        return {-Infinity, Infinity};

    if (f > 0)
        return {DivRoundDown(i.LowerBound(), f), DivRoundUp(i.UpperBound(), f)};
    else
        return {DivRoundDown(i.UpperBound(), f), DivRoundUp(i.LowerBound(), f)};
}

SAN_CPU_GPU inline Float Floor(Interval i)
{
    return std::floor(i.LowerBound());
}

SAN_CPU_GPU inline Float Ceil(Interval i)
{
    return std::ceil(i.UpperBound());
}

SAN_CPU_GPU inline Float floor(Interval i)
{
    return Floor(i);
}

SAN_CPU_GPU inline Float ceil(Interval i)
{
    return Ceil(i);
}

SAN_CPU_GPU inline Float Min(Interval a, Interval b)
{
    return std::min(a.LowerBound(), b.LowerBound());
}

SAN_CPU_GPU inline Float Max(Interval a, Interval b)
{
    return std::max(a.UpperBound(), b.UpperBound());
}

SAN_CPU_GPU inline Interval Sqrt(Interval i)
{
    return {SqrtRoundDown(i.LowerBound()), SqrtRoundUp(i.UpperBound())};
}

SAN_CPU_GPU inline Interval sqrt(Interval i)
{
    return Sqrt(i);
}

SAN_CPU_GPU inline Interval FMA(Interval a, Interval b, Interval c)
{
    Float low = std::min({FMARoundDown(a.LowerBound(), b.LowerBound(), c.LowerBound()),
                          FMARoundDown(a.UpperBound(), b.LowerBound(), c.LowerBound()),
                          FMARoundDown(a.LowerBound(), b.UpperBound(), c.LowerBound()),
                          FMARoundDown(a.UpperBound(), b.UpperBound(), c.LowerBound())});
    Float high = std::max({FMARoundUp(a.LowerBound(), b.LowerBound(), c.UpperBound()),
                           FMARoundUp(a.UpperBound(), b.LowerBound(), c.UpperBound()),
                           FMARoundUp(a.LowerBound(), b.UpperBound(), c.UpperBound()),
                           FMARoundUp(a.UpperBound(), b.UpperBound(), c.UpperBound())});
    return {low, high};
}

SAN_CPU_GPU inline Interval DifferenceOfProducts(Interval a, Interval b, Interval c,
                                                 Interval d)
{
    Float ab[4] = {a.LowerBound() * b.LowerBound(), a.UpperBound() * b.LowerBound(),
                   a.LowerBound() * b.UpperBound(), a.UpperBound() * b.UpperBound()};
    Float abLow = std::min({ab[0], ab[1], ab[2], ab[3]});
    Float abHigh = std::max({ab[0], ab[1], ab[2], ab[3]});
    int abLowIndex = abLow == ab[0] ? 0 : (abLow == ab[1] ? 1 : (abLow == ab[2] ? 2 : 3));
    int abHighIndex =
        abHigh == ab[0] ? 0 : (abHigh == ab[1] ? 1 : (abHigh == ab[2] ? 2 : 3));

    Float cd[4] = {c.LowerBound() * d.LowerBound(), c.UpperBound() * d.LowerBound(),
                   c.LowerBound() * d.UpperBound(), c.UpperBound() * d.UpperBound()};
    Float cdLow = std::min({cd[0], cd[1], cd[2], cd[3]});
    Float cdHigh = std::max({cd[0], cd[1], cd[2], cd[3]});
    int cdLowIndex = cdLow == cd[0] ? 0 : (cdLow == cd[1] ? 1 : (cdLow == cd[2] ? 2 : 3));
    int cdHighIndex =
        cdHigh == cd[0] ? 0 : (cdHigh == cd[1] ? 1 : (cdHigh == cd[2] ? 2 : 3));

// Invert cd Indices since it's subtracted...
    Float low = DifferenceOfProducts(a[abLowIndex & 1], b[abLowIndex >> 1],
                                     c[cdHighIndex & 1], d[cdHighIndex >> 1]);
    Float high = DifferenceOfProducts(a[abHighIndex & 1], b[abHighIndex >> 1],
                                      c[cdLowIndex & 1], d[cdLowIndex >> 1]);
    DCHECK_LE(low, high);

    return {NextFloatDown(NextFloatDown(low)), NextFloatUp(NextFloatUp(high))};
}

SAN_CPU_GPU inline Interval SumOfProducts(Interval a, Interval b, Interval c,
                                          Interval d)
{
    return DifferenceOfProducts(a, b, -c, d);
}

SAN_CPU_GPU inline Interval MulPow2(Float s, Interval i)
{
    return MulPow2(i, s);
}

SAN_CPU_GPU inline Interval MulPow2(Interval i, Float s)
{
    Float as = std::abs(s);
    if (as < 1)
        DCHECK_EQ(1 / as, 1ull << Log2Int(1 / as));
    else
        DCHECK_EQ(as, 1ull << Log2Int(as));

// Multiplication by powers of 2 is exaact
    return {std::min(i.LowerBound() * s, i.UpperBound() * s),
                    std::max(i.LowerBound() * s, i.UpperBound() * s)};
}

SAN_CPU_GPU inline Interval Abs(Interval i)
{
    if (i.LowerBound() >= 0)
// The entire interval is greater than zero, so we're all set.
        return i;
    else if (i.UpperBound() <= 0)
// The entire interval is less than zero.
        return {-i.UpperBound(), -i.LowerBound()};
    else
// The interval straddles zero.
        return {0, std::max(-i.LowerBound(), i.UpperBound())};
}

SAN_CPU_GPU inline Interval abs(Interval i)
{
    return Abs(i);
}

SAN_CPU_GPU inline Interval ACos(Interval i)
{
    Float low = std::acos(std::min<Float>(1, i.UpperBound()));
    Float high = std::acos(std::max<Float>(-1, i.LowerBound()));

    return {std::max<Float>(0, NextFloatDown(low)), NextFloatUp(high)};
}

SAN_CPU_GPU inline Interval Sin(Interval i)
{
    CHECK_GE(i.LowerBound(), -1e-16);
    CHECK_LE(i.UpperBound(), 2.0001 * Pi);
    Float low = std::sin(std::max<Float>(0, i.LowerBound()));
    Float high = std::sin(i.UpperBound());
    if (low > high)
        std::swap(low, high);
    low = std::max<Float>(-1, NextFloatDown(low));
    high = std::min<Float>(1, NextFloatUp(high));
    if (InRange(Pi / 2, i))
        high = 1;
    if (InRange((3.f / 2.f) * Pi, i))
        low = -1;

    return {low, high};
}

SAN_CPU_GPU inline Interval Cos(Interval i)
{
    CHECK_GE(i.LowerBound(), -1e-16);
    CHECK_LE(i.UpperBound(), 2.0001 * Pi);
    Float low = std::cos(std::max<Float>(0, i.LowerBound()));
    Float high = std::cos(i.UpperBound());
    if (low > high)
        std::swap(low, high);
    low = std::max<Float>(-1, NextFloatDown(low));
    high = std::min<Float>(1, NextFloatUp(high));
    if (InRange(Pi, i))
        low = -1;

    return {low, high};
}

SAN_CPU_GPU inline bool Quadratic(Interval a, Interval b, Interval c, Interval* t0,
                                  Interval* t1)
{
// Find quadratic discriminant
    Interval discrim = DifferenceOfProducts(b, b, MulPow2(4, a), c);
    if (discrim.LowerBound() < 0)
        return false;
    Interval floatRootDiscrim = Sqrt(discrim);

// Compute quadratic _t_ values
    Interval q{};
    if ((Float) b < 0)
        q = MulPow2(-.5, b - floatRootDiscrim);
    else
        q = MulPow2(-.5, b + floatRootDiscrim);
    *t0 = q / a;
    *t1 = c / q;
    if (t0->LowerBound() > t1->LowerBound())
        std::swap(*t0, *t1);
    return true;
}

SAN_CPU_GPU inline Interval SumSquares(Interval i)
{
    return Sqr(i);
}

template<typename... Args>
SAN_CPU_GPU inline Interval SumSquares(Interval i, Args... args)
{
    Interval ss = FMA(i, i, SumSquares(args...));
    return {std::max<Float>(0, ss.LowerBound()), ss.UpperBound()};
}

} // namespace San