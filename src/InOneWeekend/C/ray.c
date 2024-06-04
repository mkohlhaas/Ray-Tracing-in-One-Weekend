#include "camera.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"

point3
point_at (ray r, double t)
{
  return vec3_add (r.origin, vec3_scalar_mult (r.direction, t));
}

color
ray_color (ray const r, GArray *const world)
{
  hit_record rec;

  // render world
  bool       hit_anything   = false;
  double     closest_so_far = INFINITY;
  hit_record temp_rec;
  for (uint i = 0; i < world->len; i++)
    {
      hittable *h = g_array_index (world, hittable *, i);
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

// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
static vec3
sample_square (void)
{
  return (vec3){
    .x = random_double () - 0.5,
    .y = random_double () - 0.5,
    .z = 0,
  };
}

ray
get_ray (camera c, int row, int col)
{
  // Construct a camera ray originating from the origin and directed at randomly sampled
  // point around the pixel location i, j.
  vec3 offset        = sample_square ();
  vec3 pixel_sample  = vec3_add (c.pixel_origin, vec3_add (vec3_scalar_mult (c.pixel_delta_u, col + offset.x),
                                                           vec3_scalar_mult (c.pixel_delta_v, row + offset.y)));
  vec3 ray_origin    = c.center;
  vec3 ray_direction = vec3_sub (pixel_sample, ray_origin);
  return (ray){ ray_origin, ray_direction };
}
