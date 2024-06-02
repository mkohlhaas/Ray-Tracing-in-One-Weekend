#include "ray.h"
#include "color.h"
#include "point.h"
#include "sphere.h"

point3
ray_at (ray r, double t)
{
  return vec3_add (r.origin, vec3_scalar_mult (r.direction, t));
}

color
ray_color (ray const r)
{
  if (hit_sphere ((point3){ .x = 0.0, .y = 0.0, .z = -1.0 }, 0.5, r))
    {
      return (color){ .x = 1.0, .y = 0.0, .z = 0.0 };
    }

  vec3   unit_direction = vec3_unit (r.direction);
  double a              = 0.5 * (unit_direction.y + 1); // -1.0 ≤ y ≤ 1.0

  color blue = {
    .r = 0.0,
    .g = 0.0,
    .b = 1.0,
  };

  color red = {
    .r = 1.0,
    .g = 0.0,
    .b = 0.0,
  };

  color blueish = vec3_scalar_mult (blue, a);
  color whitish = vec3_scalar_mult (red, 1.0 - a);

  return vec3_add (whitish, blueish);
}
