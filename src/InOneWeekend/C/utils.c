#include "utils.h"
#include <math.h>
#include <stdlib.h>

double
degrees_to_radians (double degrees)
{
  return degrees * M_PI / 180.0;
}

// Returns a random real in [0,1).
double
random_double (void)
{
  return rand () / (RAND_MAX + 1.0);
}

// Returns a random real in [min,max).
double
random_double_min_max (double min, double max)
{
  return min + (max - min) * random_double ();
}

// gamma 2
double
linear_to_gamma (double linear_component)
{
  if (linear_component > 0)
    {
      return sqrt (linear_component);
    }
  return 0;
}

inline double
squared (double x)
{
  return x * x;
}
