#include "math/interval.h"
#include <math.h>

interval_t const intvl_empty    = { +INFINITY, -INFINITY };
interval_t const intvl_universe = { -INFINITY, +INFINITY };

double
intvl_size (interval_t intvl)
{
  return intvl.high - intvl.low;
}

// Value `x` is in interval `intvl`.
bool
intvl_contains (interval_t intvl, double x)
{
  return intvl.low <= x && x <= intvl.high;
}

bool
intvl_surrounds (interval_t intvl, double x)
{
  return intvl.low < x && x < intvl.high;
}

double
intvl_clamp (interval_t intvl, double x)
{
  return x < intvl.low ? intvl.low : x > intvl.high ? intvl.high : x;
}

interval_t
intvl_expand (interval_t intvl, double delta)
{
  auto padding = delta / 2;
  return (interval_t){ intvl.low - padding, intvl.high + padding };
}

// Create the interval tightly enclosing the two input intervals `a` and `b`.
interval_t
intvl_from_intvls (interval_t const a, interval_t const b)
{
  auto min = fmin (a.low, b.low);
  auto max = fmax (a.high, b.high);
  return (interval_t){ min, max };
}

interval_t
intvl_add_displacement (interval_t const intvl, double displacement)
{
  return (interval_t){ intvl.low + displacement, intvl.high + displacement };
}
