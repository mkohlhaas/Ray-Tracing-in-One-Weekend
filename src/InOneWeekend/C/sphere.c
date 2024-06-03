#include "sphere.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>

bool
hit_sphere (void *self, ray const r, double tmin, double tmax, hit_record *rec)
{
  sphere *s    = self;
  vec3    c_q  = vec3_sub (s->center, r.origin);
  double  a    = vec3_length_squared (r.direction);
  double  h    = vec3_dot_product (r.direction, c_q);
  double  c    = vec3_length_squared (c_q) - (s->radius * s->radius);
  double  disc = h * h - a * c;

  if (disc < 0)
    {
      return false;
    }

  double sqrtd = sqrt (disc);

  // Find the nearest root that lies in the acceptable range.
  double root = (h - sqrtd) / a;
  if (root <= tmin || tmax <= root)
    {
      root = (h + sqrtd) / a;
      if (root <= tmin || tmax <= root)
        {
          return false;
        }
    }

  rec->t              = root;
  rec->p              = point_at (r, root);
  vec3 outward_normal = vec3_scalar_div (vec3_sub (rec->p, s->center), s->radius);
  set_face_normal (rec, r, outward_normal);

  return true;
}
