#include "sphere.h"
#include <math.h>

// Return the t in P(t) = Q + td.
// Negative if not hit.
double
hit_sphere (point3 const center, double radius, ray const r)
{
  vec3   c_q  = vec3_sub (center, r.origin);
  double a    = vec3_dot_product (r.direction, r.direction);
  double b    = -2.0 * vec3_dot_product (r.direction, c_q);
  double c    = vec3_dot_product (c_q, c_q) - (radius * radius);
  double disc = b * b - 4 * a * c;

  if (disc < 0)
    {
      return -1.0;
    }
  else
    {
      return (-b - sqrt (disc)) / (2.0 * a);
    }
}
