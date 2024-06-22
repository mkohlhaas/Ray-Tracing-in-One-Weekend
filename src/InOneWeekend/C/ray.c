#include "ray.h"
#include "material.h"
#include "stb_ds.h"
#include "utils.h"
#include <math.h>

ray_t *
ray_new (point3 origin, vec3_t direction)
{
  ray_t *r = malloc (sizeof (*r));
  if (r)
    {
      r->origin    = origin;
      r->direction = direction;
    }
  return r;
}

point3
point_at (ray_t r, double t)
{
  return vec3_add (r.origin, vec3_scalar_mult (r.direction, t));
}

color_t
ray_color (ray_t const ray, int depth, hit_able_t *world[])
{
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    {
      return black;
    }

  // render world
  bool         hit_anything   = false;
  double       closest_so_far = INFINITY;
  hit_record_t hit_rec;
  hit_record_t obj_hit;
  for (uint i = 0; i < arrlen (world); i++)
    {
      obj_hit.object = world[i];
      if (obj_hit.object->hit_fn (ray, (interval_t){ 0.001, closest_so_far }, &obj_hit))
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
      ray_t   scattered;
      color_t attenuation;

      material_t *mat = get_material (hit_rec.object);
      mat->scatter (ray, &hit_rec, &attenuation, &scattered);
      return vec3_mul (attenuation, ray_color (scattered, depth - 1, world));
    }

  // render background
  vec3_t unit_direction = vec3_unit (ray.direction);
  double a              = 0.5 * (unit_direction.y + 1); // -1.0 ≤ y ≤ 1.0 ⇒ 0.0 ≤ a ≤ 1.0

  color_t blueish = vec3_scalar_mult (light_blue, a);
  color_t whitish = vec3_scalar_mult (white, 1.0 - a);

  return vec3_add (whitish, blueish);
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

static point3
defocus_disk_sample ()
{
  // Returns a random point in the camera defocus disk.
  auto p = vec3_random_in_unit_disk ();
  return vec3_add (vec3_add (g_camera.lookfrom, vec3_scalar_mult (g_camera.defocus_disk_u, p.x)),
                   vec3_scalar_mult (g_camera.defocus_disk_v, p.y));
}

// Construct a camera ray originating from the defocus disk and directed
// at a randomly sampled point around the pixel location row, col.
ray_t
random_ray (camera_t cam, int row, int col)
{
  vec3_t offset        = sample_square ();
  auto   p_u           = vec3_scalar_mult (cam.pixel_delta_u, col + offset.x);
  auto   p_v           = vec3_scalar_mult (cam.pixel_delta_v, row + offset.y);
  auto   p_u_v         = vec3_add (p_u, p_v);
  vec3_t pixel_sample  = vec3_add (cam.pixel_origin, p_u_v);
  point3 ray_origin    = (cam.defocus_angle <= 0) ? cam.lookfrom : defocus_disk_sample ();
  vec3_t ray_direction = vec3_sub (pixel_sample, ray_origin);
  return (ray_t){ ray_origin, ray_direction };
}

// The parameter `outward_normal` is assumed to have unit length.
void
set_face_normal (hit_record_t *rec, ray_t const r, vec3_t const outward_unit_normal)
{
  rec->front_face = vec3_dot (r.direction, outward_unit_normal) < 0;
  rec->normal     = rec->front_face ? outward_unit_normal : vec3_minus (outward_unit_normal);
}
