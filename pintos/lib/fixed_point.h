#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>

//every fixed point value is a multiple of the real number 1/FRACTION
#define FRACTION (1 << 14)

typedef struct fp
{
  int32_t v;
} fp_t;

static inline int
fp_floor (fp_t n)
{
  return n.v / FRACTION;
}

static inline int
fp_round_nearest (fp_t n)
{
  n.v += FRACTION / 2;
  return fp_floor (n);
}

static inline fp_t
fp_from_int (int i)
{
  fp_t result = { i * FRACTION };
  return result;
}

static inline fp_t
fp_add (fp_t a, fp_t b)
{
  fp_t result = { a.v + b.v };
  return result;
}

static inline fp_t
fp_sub (fp_t a, fp_t b)
{
  fp_t result = { a.v - b.v };
  return result;
}

static inline fp_t
fp_mul (fp_t a, fp_t b)
{
  int64_t temp = (int64_t)a.v * (int64_t)b.v;
  fp_t result = { temp / (int64_t)FRACTION };
  return result;
}

static inline fp_t
fp_div (fp_t a, fp_t b)
{
  int64_t temp = (int64_t)a.v * (int64_t)FRACTION;
  fp_t result = { temp / (int64_t)b.v };
  return result;
}

#endif

