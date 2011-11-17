#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>

//every fixed point value is a multiple of the real number 1/FRACTION
#define FRACTION (1 << 14)

typedef int32_t fp_t;

static inline int
fp_floor (fp_t n)
{
  return i / FRACTION;
}

static inline int
fp_round_nearest (fp_t n)
{
  n += FRACTION / 2;
  ASSERT (n >= FRACTION / 2);
  return fp_floor (result);
}

static inline fp_t
fp_from_int (int i)
{
  ASSERT (i <= fp_floor (INT32_MAX));
  return i * FRACTION;
}

static inline fp_t
fp_add (fp_t a, fp_t b)
{
  return a + b;
}

static inline fp_t
fp_subtract (fp_t a, fp_t b)
{
  return a - b;
}

static inline fp_t
fp_multiply (fp_t a, fp_t b)
{
  int64_t result = (int64_t)a * (int64_t)b;
  result /= FRACTION;
  return (fp_t)result;
}

static inline fp_t
fp_divide (fp_t a, fp_t b)
{
  int64_t result = (int64_t)a * (int64_t)FRACTION;
  result /= b;
  ASSERT (result <= (int64_t)UINT32_MAX);
  return (fp_t)result;
}

static inline fp_t
fp_pow (fp_t base, int exp)
{
  fp_t result = fp_from_int (1);
  for (; exp > 0; --exp)
    result = fp_multiply (result, base);
  for (; exp < 0; ++exp)
    result = fp_divide (result, base);
  return result;
}
#endif

