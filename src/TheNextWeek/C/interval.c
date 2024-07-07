#include "interval.h"
#include <math.h>

interval_t const intvl_empty    = { +INFINITY, -INFINITY };
interval_t const intvl_universe = { -INFINITY, +INFINITY };

double
intvl_size (interval_t intvl)
{
  return intvl.max - intvl.min;
}

bool
intvl_contains (interval_t intvl, double x)
{
  return intvl.min <= x && x <= intvl.max;
}

bool
intvl_surrounds (interval_t intvl, double x)
{
  return intvl.min < x && x < intvl.max;
}

double
intvl_clamp (interval_t intvl, double x)
{
  return x < intvl.min ? intvl.min : x > intvl.max ? intvl.max : x;
}

interval_t
intvl_expand (interval_t intvl, double delta)
{
  auto padding = delta / 2;
  return (interval_t){ intvl.min - padding, intvl.max + padding };
}

// Create the interval tightly enclosing the two input intervals `a` and `b`.
interval_t
intvl_from_intvls (interval_t const a, interval_t const b)
{
  auto min = a.min <= b.min ? a.min : b.min;
  auto max = a.max >= b.max ? a.max : b.max;
  return (interval_t){ min, max };
}
