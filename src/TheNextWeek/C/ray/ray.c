#include "ray/ray.h"
#include "3rd_party/stb_ds.h"
#include "globals/globals.h"
#include "materials/material.h"
#include "math/color.h"
#include "math/interval.h"
#include "utils/utils.h"
#include "vec3.h"
#include <math.h>

point3_t
point_at (ray_t r, double t)
{
  return vec3_add (r.origin, vec3_mult (t, r.direction));
}

// static color_t
// render_background (ray_t const ray)
// {
//   vec3_t unit_direction = vec3_unit (ray.direction);
//   double a              = 0.5 * (unit_direction.y + 1); // -1.0 ≤ y ≤ 1.0 ⇒ 0.0 ≤ a ≤ 1.0
//   return lerp (light_blue, white, a);
// }

// Recursive function to calculate effective color.
color_t
ray_color (ray_t const ray, int depth, hittable_t *world)
{
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    {
      return black;
    }

  // render world
  double       closest_so_far = INFINITY;
  hit_record_t hit_rec;
  bool         got_hit = world->hit (ray, world, (interval_t){ g_min_t, closest_so_far }, &hit_rec);

  if (got_hit)
    {
      material_t *mat = get_material (hit_rec.object);

      color_t color_from_emission = mat->emit (&hit_rec);

      ray_t   scattered;
      color_t attenuation;
      if (mat->scatter (ray, &hit_rec, &attenuation, &scattered))
        {
          color_t color_from_scatter = vec3_mulv (attenuation, ray_color (scattered, depth - 1, world));

          return vec3_add (color_from_emission, color_from_scatter);
        }
      else
        {
          return color_from_emission;
        }
    }
  else
    {
      return g_background;
    }
}

// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
static vec3_t
sample_square (void)
{
  return (vec3_t){
    .x = random_double () - 0.5,
    .y = random_double () - 0.5,
    .z = 0,
  };
}

// Returns a random point in the camera defocus disk.
static point3_t
defocus_disk_sample ()
{
  auto p   = vec3_random_in_unit_disk ();
  auto u   = vec3_mult (p.x, g_camera.defocus_disk_u);
  auto v   = vec3_mult (p.y, g_camera.defocus_disk_v);
  auto u_v = vec3_add (u, v);
  return vec3_add (g_camera.lookfrom, u_v);
}

// Construct a camera ray originating from the defocus disk and directed
// at a randomly sampled point around the pixel location row, col.
ray_t
random_ray (camera_t cam, int row, int col)
{
  auto offset        = sample_square ();
  auto p_u           = vec3_mult (col + offset.x, cam.pixel_delta_u);
  auto p_v           = vec3_mult (row + offset.y, cam.pixel_delta_v);
  auto p_u_v         = vec3_add (p_u, p_v);
  auto pixel_sample  = vec3_add (cam.pixel_origin, p_u_v);
  auto ray_origin    = (cam.defocus_angle <= 0) ? cam.lookfrom : defocus_disk_sample ();
  auto ray_direction = vec3_sub (pixel_sample, ray_origin);
  auto ray_time      = random_double ();
  return (ray_t){ ray_origin, ray_direction, ray_time };
}

// The parameter `outward_normal` is assumed to have unit length.
void
set_face_normal (hit_record_t *rec, ray_t const r, vec3_t const outward_unit_normal)
{
  rec->front_face  = vec3_dot (r.direction, outward_unit_normal) < 0;
  rec->unit_normal = rec->front_face ? outward_unit_normal : vec3_uminus (outward_unit_normal);
}
