#include "ray.h"
#include "color.h"
#include "point.h"
#include "sphere.h"
#include "vec3.h"

point3
point_at (ray r, double t)
{
  return vec3_add (r.origin, vec3_scalar_mult (r.direction, t));
}

color
ray_color (ray const r)
{
  // sphere
  double t = hit_sphere ((point3){ .x = 0.0, .y = 0.0, .z = -1.0 }, 0.5, r);
  if (t > 0.0)
    {
      point3 P = point_at (r, t);
      point3 C = (vec3){
        .x = 0.0,
        .y = 0.0,
        .z = -1.0,
      };
      vec3 N = vec3_unit (vec3_sub (P, C));

      return vec3_scalar_mult (
          (color){
              .r = N.x + 1,
              .g = N.y + 1,
              .b = N.z + 1,
          },
          0.5);
    }

  // background
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
