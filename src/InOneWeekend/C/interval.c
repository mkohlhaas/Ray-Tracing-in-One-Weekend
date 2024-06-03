#include "interval.h"
#include <math.h>

double
size (interval i)
{
  return i.max - i.min;
}

bool
contains (interval i, double x)
{
  return i.min <= x && x <= i.max;
}

bool
surrounds (interval i, double x)
{
  return i.min < x && x < i.max;
}

interval empty    = { +INFINITY, -INFINITY };
interval universe = { -INFINITY, +INFINITY };
