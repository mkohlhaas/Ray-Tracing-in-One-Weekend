#include "hittable.h"

point3
point_at (ray r, double t)
{
  return vec3_add (r.origin, vec3_scalar_mult (r.direction, t));
}

color
ray_color (ray const r, GArray *const world)
{
  color      blue  = { .r = 0.0, .g = 0.0, .b = 1.0 };
  color      red   = { .r = 1.0, .g = 0.0, .b = 0.0 };
  color      white = { .r = 1.0, .g = 1.0, .b = 1.0 };
  hit_record rec;

  // render world
  bool       hit_anything   = false;
  double     closest_so_far = INFINITY;
  hit_record temp_rec;
  for (uint i = 0; i < world->len; i++)
    {
      hittable *h = g_array_index (world, hittable*, i);
      if (h->hit (h->object, r, (interval){ 0, closest_so_far }, &temp_rec))
        {
          hit_anything = true;
          if (temp_rec.t < closest_so_far)
            {
              rec            = temp_rec;
              closest_so_far = rec.t;
            }
        };
    }
  if (hit_anything)
    {
      return vec3_scalar_mult (vec3_add (rec.normal, white), 0.5);
    }

  // render background
  vec3   unit_direction = vec3_unit (r.direction);
  double a              = 0.5 * (unit_direction.y + 1); // -1.0 ≤ y ≤ 1.0 ⇒ 0.0 ≤ a ≤ 1.0

  color blueish = vec3_scalar_mult (blue, a);
  color whitish = vec3_scalar_mult (red, 1.0 - a);

  return vec3_add (whitish, blueish);
}
