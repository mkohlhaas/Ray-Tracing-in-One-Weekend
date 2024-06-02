#include "sphere.h"
#include "vec3.h"
#include <math.h>

// Return the t in P(t) = Q + td. (Negative if no hit.)
double
hit_sphere (point3 const center, double radius, ray const r)
{
  vec3   c_q  = vec3_sub (center, r.origin);
  double a    = vec3_length_squared (r.direction);
  double h    = vec3_dot_product (r.direction, c_q);
  double c    = vec3_length_squared (c_q) - (radius * radius);
  double disc = h * h - a * c;

  if (disc < 0)
    {
      return -1.0;
    }
  else
    {
      return (h - sqrt (disc)) / a;
    }
}
