#include "ray.h"
#include "vec3.h"

point3
ray_at (ray r, double t)
{
  return vec3_add (r.orig, vec3_scalar_mult (r.dir, t));
}
