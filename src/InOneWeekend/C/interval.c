#include "interval.h"
#include <math.h>

double
itvl_size (interval i)
{
  return i.max - i.min;
}

bool
itvl_contains (interval i, double x)
{
  return i.min <= x && x <= i.max;
}

bool
itvl_surrounds (interval i, double x)
{
  return i.min < x && x < i.max;
}

double
itvl_clamp (interval i, double x)
{
  return x < i.min ? i.min : x > i.max ? i.max : x;
}

interval empty    = { +INFINITY, -INFINITY };
interval universe = { -INFINITY, +INFINITY };
