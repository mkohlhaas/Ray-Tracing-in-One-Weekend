#include "ray.h"
#include "camera.h"
#include "hit_record.h"
#include "hittable.h"
#include "stb_ds.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>

ray *
ray_new (point3 origin, vec3 direction)
{
  ray *r = malloc (sizeof (*r));
  if (r)
    {
      r->origin    = origin;
      r->direction = direction;
    }
  return r;
}

point3
point_at (ray r, double t)
{
  return vec3_add (r.origin, vec3_scalar_mult (r.direction, t));
}

color
ray_color (ray const r, int depth, hittable *world[])
{
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    {
      return black;
    }

  // render world
  bool       hit_anything   = false;
  double     closest_so_far = INFINITY;
  hit_record hit_rec;
  hit_record obj_hit;
  for (uint i = 0; i < arrlen (world); i++)
    {
      hittable *h = world[i];
      if (h->hit (h->object, r, (interval){ 0.001, closest_so_far }, &obj_hit))
        {
          hit_anything = true;
          if (obj_hit.t < closest_so_far)
            {
              hit_rec        = obj_hit;
              closest_so_far = hit_rec.t;
            }
        };
    }
  if (hit_anything)
    {
      ray   scattered;
      color attenuation;
      if (hit_rec.mat->scatter (hit_rec.mat->self, r, &hit_rec, &attenuation, &scattered))
        {
          return vec3_mul (attenuation, ray_color (scattered, depth - 1, world));
        }
      return black;
    }

  // render background
  vec3   unit_direction = vec3_unit (r.direction);
  double a              = 0.5 * (unit_direction.y + 1); // -1.0 ≤ y ≤ 1.0 ⇒ 0.0 ≤ a ≤ 1.0

  color blueish = vec3_scalar_mult (light_blue, a);
  color whitish = vec3_scalar_mult (white, 1.0 - a);

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
