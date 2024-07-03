#include "utils.h"
#include "color.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

// gamma 2 correction
double
linear_to_gamma (double linear_component)
{
  if (linear_component > 0)
    {
      return sqrt (linear_component);
    }
  else
    {
      return 0;
    }
}

inline double
squared (double x)
{
  return x * x;
}

char *
remove_leading_0s (char *s)
{
  while (*s == '0' && strlen (s) > 1)
    {
      s++;
    }
  return s;
}

// `a` should be in the range [0;1]
color_t
lerp (color_t start_color, color_t end_color, double a)
{
  color_t c1 = vec3_mult (a, start_color);
  color_t c2 = vec3_mult (1.0 - a, end_color);
  return vec3_add (c1, c2);
}
