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
double sin(double x) __WEAK_SYMBOL;
float sinf(float x) __WEAK_SYMBOL;

// _math_powabs.c
double pow(double x, double y) __WEAK_SYMBOL;
float powf(float x, float y) __WEAK_SYMBOL;

#undef __WEAK_SYMBOL

#ifdef __cplusplus
}
#endif

#endif /* MATH_H_ */
