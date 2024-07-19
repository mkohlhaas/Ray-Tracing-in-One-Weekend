#include "sphere.h"
#include "aabb.h"
#include "point.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// `p` is a given point on the unit sphere, centered at the origin.
// `u` is the returned value [0,1] of the angle around the Y axis from X=-1.
// `v` is the returned value [0,1] of the angle from Y=-1 to Y=+1.
//  <1 0 0> yields <0.50 0.50>, <-1  0  0> yields <0.00 0.50>,
//  <0 1 0> yields <0.50 1.00>, < 0 -1  0> yields <0.50 0.00>,
//  <0 0 1> yields <0.25 0.50>, < 0  0 -1> yields <0.75 0.50>,
static void
set_texture_coords (point3_t const *p, double *u, double *v)
{
  auto theta = acos (-p->y);
  auto phi   = atan2 (-p->z, p->x) + M_PI;

  *u = phi / (2 * M_PI);
  *v = theta / M_PI;
}

// Linearly interpolate from center_start to center_end according to time `tm`,
// where `tm` = 0 yields center_start, and `tm` = 1 yields center_end.
static point3_t
sphere_center (sphere_t *s, double tm)
{
  return vec3_add (s->center_start, vec3_mult (tm, s->center_vec));
}

// `object` in `rec` must be set before calling this function.
// Returns `false` if disc is too small, otherwise `true`.
// Returns `hit_record` in `rec`.
static bool
sphere_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  sphere_t *s    = (sphere_t *)object;
  vec3_t    c_q  = vec3_sub (sphere_center (s, ray.tm), ray.origin);
  double    a    = vec3_length_squared (ray.direction);
  double    h    = vec3_dot (ray.direction, c_q);
  double    c    = vec3_length_squared (c_q) - squared (s->radius);
  double    disc = h * h - a * c;

  if (disc < 0)
    {
      return false;
    }

  double sqrtd = sqrt (disc);

  // Find the nearest root that lies in the acceptable range.
  double root = (h - sqrtd) / a;
  if (!intvl_surrounds (intvl, root))
    {
      root = (h + sqrtd) / a;
      if (!intvl_surrounds (intvl, root))
        {
          return false;
        }
    }

  rec->object           = object;
  rec->t                = root;
  rec->p                = point_at (ray, root);
  vec3_t outward_normal = vec3_divt (vec3_sub (rec->p, s->center_start), s->radius);
  set_face_normal (rec, ray, outward_normal);
  set_texture_coords (&outward_normal, &rec->u, &rec->v);

  return true;
}

// Returns `NULL` if memory allocation failed.
sphere_t *
sphere_new (point3_t center_start, point3_t center_end, double radius, material_t *mat)
{
  sphere_t *s = malloc (sizeof (*s));
  if (s)
    {
      s->hit_type     = SPHERE;
      s->hit          = sphere_hit;
      s->center_start = center_start;
      s->center_vec   = vec3_sub (center_end, center_start);
      s->radius       = radius;
      s->mat          = mat;

      auto rvec = (vec3_t){ .x = radius, .y = radius, .z = radius };

      auto box1_min = vec3_sub (center_start, rvec);
      auto box1_max = vec3_add (center_start, rvec);
      auto box2_min = vec3_sub (center_end, rvec);
      auto box2_max = vec3_add (center_end, rvec);

      auto box1 = aabb_from_points (&box1_min, &box1_max);
      auto box2 = aabb_from_points (&box2_min, &box2_max);

      s->bbox = aabb_from_aabbs (&box1, &box2);
    }
  return s;
}

void
sphere_print (sphere_t *s, int indent_lvl)
{
  fprintf (stderr, "%*sSphere (%f %f) (%f %f) (%f %f)\n", indent_lvl, "", s->bbox.x_intvl.low, s->bbox.x_intvl.high,
           s->bbox.y_intvl.low, s->bbox.y_intvl.high, s->bbox.z_intvl.low, s->bbox.z_intvl.high);
}
