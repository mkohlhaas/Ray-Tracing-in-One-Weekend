#include "sphere.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>
#include <stdlib.h>

// Linearly interpolate from center_start to center_end according to time `tm`,
// where `tm` = 0 yields center_start, and `tm` = 1 yields center_end.
static point3
sphere_center (sphere_t *s, double tm)
{
  return vec3_add (s->center_start, vec3_mult (tm, s->center_vec));
}

// Returns false if disc is too small otherwise true.
// Returns `hit_record` in `rec`.
static bool
sphere_hit (ray_t const ray, interval_t itvl, hit_record_t *rec)
{
  sphere_t *s    = (sphere_t *)rec->object;
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
  if (!itvl_surrounds (itvl, root))
    {
      root = (h + sqrtd) / a;
      if (!itvl_surrounds (itvl, root))
        {
          return false;
        }
    }

  rec->t                = root;
  rec->p                = point_at (ray, root);
  vec3_t outward_normal = vec3_divt (vec3_sub (rec->p, s->center_start), s->radius);
  set_face_normal (rec, ray, outward_normal);

  return true;
}

// Returns NULL if memory allocation failed.
sphere_t *
sphere_new (point3 center_start, point3 center_end, double radius, material_t *mat)
{
  sphere_t *s = malloc (sizeof (*s));
  if (s)
    {
      s->type         = SPHERE;
      s->hit_fn       = sphere_hit;
      s->center_start = center_start;
      s->center_vec   = vec3_sub (center_end, center_start);
      s->radius       = radius;
      s->mat          = mat;
    }
  return s;
}
