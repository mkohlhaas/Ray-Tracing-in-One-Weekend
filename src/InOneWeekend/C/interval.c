#include "interval.h"
#include <math.h>

double
itvl_size (interval_t i)
{
  return i.max - i.min;
}

bool
itvl_contains (interval_t i, double x)
{
  return i.min <= x && x <= i.max;
}

bool
itvl_surrounds (interval_t i, double x)
{
  return i.min < x && x < i.max;
}

double
itvl_clamp (interval_t i, double x)
{
  return x < i.min ? i.min : x > i.max ? i.max : x;
}

interval_t empty    = { +INFINITY, -INFINITY };
interval_t universe = { -INFINITY, +INFINITY };
