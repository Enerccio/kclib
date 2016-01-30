/*
 * math.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef MATH_H_
#define MATH_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>

#ifdef __INCLUDED_FROM_CLIB
#define __WEAK_SYMBOL __attribute__((weak))
#else
#define __WEAK_SYMBOL
#endif

#include <stdint.h>
typedef union { uint32_t iv; float f; } __float_converter;
typedef union { uint64_t iv; double d; } __double_converter;

#if FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 1
typedef double float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 2
#error Long double is not supported
typedef long double float_t;
typedef long double double_t;
#else
typedef float float_t;
typedef float double_t;
#endif

#define HUGE_VAL  __DBL_MAX__
#define HUGE_VALF __FLT_MAX__
#define HUGE_VALL __LDBL_MAX__

#ifndef INFINITY
static const __float_converter __flt_cnv_inf = {0x7F800000};
#define INFINITY (__flt_cnv_inf.f)
#endif

#ifndef NAN
static const __float_converter __flt_cnv_nan = {0x7FC00000};
#define NAN (__flt_cnv_nan.f)
#endif

#ifndef __DINFINITY
static const __double_converter __dbl_cnv_inf = {0x7FF0000000000000};
#define __DINFINITY (__dbl_cnv_inf.d)
#endif

#ifndef __DNAN
static const __double_converter __dbl_cnv_nan = {0x7FFFFFFFFFFFFFFF};
#define __DNAN (__dbl_cnv_nan.d)
#endif

#define FP_INFINITE  (0)
#define FP_NAN		 (1)
#define FP_NORMAL	 (2)
#define FP_SUBNORMAL (3)
#define FP_ZERO		 (4)

#ifndef FP_ILOGB0
#define FP_ILOGB0 (-INT_MAX)
#endif
#ifndef FP_ILOGBNAN
#define FP_ILOGBNAN INT_MAX
#endif

#define MATH_ERRNO     (1)
#define MATH_ERREXCEPT (2)

#define math_errhandling MATH_ERRNO

int __fpclassify_f(float x);
int __fpclassify_d(double x);

#define fpclassify(x) ((sizeof(x) == sizeof(float)) ? __fpclassify_f(x) : __fpclassify_d(x))

#define isfinite(x) (!(isinf(x)) || isnan(x))
#define isnan(x) (fpclassify(x) & FP_NAN)
#define isinf(x) (fpclassify(x) & FP_INFINITE)
#define isnormal(x) (fpclassify(x) & FP_NORMAL)

int __signbit_f(float x);
int __signbit_d(double x);

#define signbit(x) ((sizeof(x) == sizeof(float)) ? __signbit_f(x) : __signbit_d(x))

// _math_gonio.c
double acos(double x) __WEAK_SYMBOL;
float acosf(float x) __WEAK_SYMBOL;
double asin(double x) __WEAK_SYMBOL;
float asinf(float x) __WEAK_SYMBOL;
double atan(double x) __WEAK_SYMBOL;
float atanf(float x) __WEAK_SYMBOL;
double atan2(double y, double x) __WEAK_SYMBOL;
float atan2f(float y, float x) __WEAK_SYMBOL;
double cos(double x) __WEAK_SYMBOL;
float cosf(float x) __WEAK_SYMBOL;
double sin(double x) __WEAK_SYMBOL;
float sinf(float x) __WEAK_SYMBOL;
double tan(double x) __WEAK_SYMBOL;
float tanf(float x) __WEAK_SYMBOL;
double acosh(double x) __WEAK_SYMBOL;
float acoshf(float x) __WEAK_SYMBOL;
double asinh(double x) __WEAK_SYMBOL;
float asinhf(float x) __WEAK_SYMBOL;
double atanh(double x) __WEAK_SYMBOL;
float atanhf(float x) __WEAK_SYMBOL;
double cosh(double x) __WEAK_SYMBOL;
float coshf(float x) __WEAK_SYMBOL;
double sinh(double x) __WEAK_SYMBOL;
float sinhf(float x) __WEAK_SYMBOL;
double tanh(double x) __WEAK_SYMBOL;
float tanhf(float x) __WEAK_SYMBOL;

// _math_exlog.c
double exp(double x) __WEAK_SYMBOL;
float expf(float x) __WEAK_SYMBOL;
double exp2(double x) __WEAK_SYMBOL;
float exp2f(float x) __WEAK_SYMBOL;
double expm1(double x) __WEAK_SYMBOL;
float expm1f(float x) __WEAK_SYMBOL;
double frexp(double value, int *exp) __WEAK_SYMBOL;
float frexpf(float value, int *exp) __WEAK_SYMBOL;
int ilogb(double x) __WEAK_SYMBOL;
int ilogbf(float x) __WEAK_SYMBOL;
double ldexp(double x, int exp) __WEAK_SYMBOL;
float ldexpf(float x, int exp) __WEAK_SYMBOL;
double log(double x) __WEAK_SYMBOL;
float logf(float x) __WEAK_SYMBOL;
double log10(double x) __WEAK_SYMBOL;
float log10f(float x) __WEAK_SYMBOL;
double log1p(double x) __WEAK_SYMBOL;
float log1pf(float x) __WEAK_SYMBOL;
double log2(double x) __WEAK_SYMBOL;
float log2f(float x) __WEAK_SYMBOL;
double logb(double x) __WEAK_SYMBOL;
float logbf(float x) __WEAK_SYMBOL;
double scalbn(double x, int n) __WEAK_SYMBOL;
float scalbnf(float x, int n) __WEAK_SYMBOL;
double scalbln(double x, long int n) __WEAK_SYMBOL;
float scalblnf(float x, long int n) __WEAK_SYMBOL;
double cbrt(double x) __WEAK_SYMBOL;
float cbrtf(float x) __WEAK_SYMBOL;
double hypot(double x, double y) __WEAK_SYMBOL;
float hypotf(float x, float y) __WEAK_SYMBOL;
double sqrt(double x) __WEAK_SYMBOL;
float sqrtf(float x) __WEAK_SYMBOL;
double lgamma(double x) __WEAK_SYMBOL;
float lgammaf(float x) __WEAK_SYMBOL;
double tgamma(double x) __WEAK_SYMBOL;
float tgammaf(float x) __WEAK_SYMBOL;

// _math_err.c
double erf(double x) __WEAK_SYMBOL;
float erff(float x) __WEAK_SYMBOL;
double erfc(double x) __WEAK_SYMBOL;
float erfcf(float x) __WEAK_SYMBOL;

// _math_powabs.c
double pow(double x, double y) __WEAK_SYMBOL;
float powf(float x, float y) __WEAK_SYMBOL;
double fabs(double x) __WEAK_SYMBOL;
float fabsf(float x) __WEAK_SYMBOL;

// _math_rounds.c
double ceil(double x) __WEAK_SYMBOL;
float ceilf(float x) __WEAK_SYMBOL;
double floor(double x) __WEAK_SYMBOL;
float floorf(float x) __WEAK_SYMBOL;
double nearbyint(double x) __WEAK_SYMBOL;
float nearbyintf(float x) __WEAK_SYMBOL;
double rint(double x) __WEAK_SYMBOL;
float rintf(float x) __WEAK_SYMBOL;
long int lrint(double x) __WEAK_SYMBOL;
long int lrintf(float x) __WEAK_SYMBOL;
long long int llrint(double x) __WEAK_SYMBOL;
long long int llrintf(float x) __WEAK_SYMBOL;
double round(double x) __WEAK_SYMBOL;
float roundf(float x) __WEAK_SYMBOL;
long int lround(double x) __WEAK_SYMBOL;
long int lroundf(float x) __WEAK_SYMBOL;
long long int llround(double x) __WEAK_SYMBOL;
long long int llroundf(float x) __WEAK_SYMBOL;
double trunc(double x) __WEAK_SYMBOL;
float truncf(float x) __WEAK_SYMBOL;

// _math_rem.c
double modf(double value, double *iptr) __WEAK_SYMBOL;
float modff(float value, float *iptr) __WEAK_SYMBOL;
double fmod(double x, double y) __WEAK_SYMBOL;
float fmodf(float x, float y) __WEAK_SYMBOL;
double remainder(double x, double y) __WEAK_SYMBOL;
float remainderf(float x, float y) __WEAK_SYMBOL;
double remquo(double x, double y, int *quo) __WEAK_SYMBOL;
float remquof(float x, float y, int *quo) __WEAK_SYMBOL;

// _math_manip.c
double copysign(double x, double y) __WEAK_SYMBOL;
float copysignf(float x, float y) __WEAK_SYMBOL;
double nan(const char *tagp) __WEAK_SYMBOL;
float nanf(const char *tagp) __WEAK_SYMBOL;
double nextafter(double x, double y) __WEAK_SYMBOL;
float nextafterf(float x, float y) __WEAK_SYMBOL;
double nexttoward(double x, long double y) __WEAK_SYMBOL;
float nexttowardf(float x, long double y) __WEAK_SYMBOL;

// _math_diff.c
double fdim(double x, double y) __WEAK_SYMBOL;
float fdimf(float x, float y) __WEAK_SYMBOL;
double fmax(double x, double y) __WEAK_SYMBOL;
float fmaxf(float x, float y) __WEAK_SYMBOL;
double fmin(double x, double y) __WEAK_SYMBOL;
float fminf(float x, float y) __WEAK_SYMBOL;
double fma(double x, double y, double z) __WEAK_SYMBOL;
float fmaf(float x, float y, float z) __WEAK_SYMBOL;

#define isgreater(x, y)
#define isgreaterequal(x, y)
#define isless(x, y)
#define islessequal(x, y)
#define islessgreater(x, y)
#define isunordered(x, y)


#undef __WEAK_SYMBOL

#ifdef __cplusplus
}
#endif

#endif /* MATH_H_ */
