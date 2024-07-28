#include "rotate_y.h"
#include "aabb.h"
#include "hittable.h"
#include "interval.h"
#include "point.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>
#include <stdlib.h>

static bool
rotate_y_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  rotate_y_t *ry = (rotate_y_t *)object;

  auto origin    = ray.origin;
  auto direction = ray.direction;

  origin.element[0] = ry->cos_theta * ray.origin.element[0] - ry->sin_theta * ray.origin.element[2];
  origin.element[2] = ry->sin_theta * ray.origin.element[0] + ry->cos_theta * ray.origin.element[2];

  direction.element[0] = ry->cos_theta * ray.direction.element[0] - ry->sin_theta * ray.direction.element[2];
  direction.element[2] = ry->sin_theta * ray.direction.element[0] + ry->cos_theta * ray.direction.element[2];

  auto rotated_r = (ray_t){ origin, direction, ray.tm };

  // Determine whether an intersection exists in object space (and if so, where)
  if (!ry->object->hit (rotated_r, ry->object, intvl, rec))
    {
      return false;
    }

  // Change the intersection point from object space to world space
  auto p       = rec->p;
  p.element[0] = ry->cos_theta * rec->p.element[0] + ry->sin_theta * rec->p.element[2];
  p.element[2] = -ry->sin_theta * rec->p.element[0] + ry->cos_theta * rec->p.element[2];

  // Change the normal from object space to world space
  auto normal       = rec->unit_normal;
  normal.element[0] = ry->cos_theta * rec->unit_normal.element[0] + ry->sin_theta * rec->unit_normal.element[2];
  normal.element[2] = -ry->sin_theta * rec->unit_normal.element[0] + ry->cos_theta * rec->unit_normal.element[2];

  rec->p           = p;
  rec->unit_normal = normal;

  return true;
}

rotate_y_t *
rotate_y_new (hittable_t *object, double angle)
{
  rotate_y_t *r = malloc (sizeof (*r));
  if (r)
    {
      auto radians = degrees_to_radians (angle);
      r->sin_theta = sin (radians);
      r->cos_theta = cos (radians);
      r->bbox      = object->bbox;

      auto min = (point3_t){ .x = INFINITY, .y = INFINITY, .z = INFINITY };
      auto max = (point3_t){ .x = -INFINITY, .y = -INFINITY, .z = -INFINITY };

      for (int i = 0; i < 2; i++)
        {
          for (int j = 0; j < 2; j++)
            {
              for (int k = 0; k < 2; k++)
                {
                  auto x = i * r->bbox.x_intvl.low + (1 - i) * r->bbox.x_intvl.low;
                  auto y = j * r->bbox.y_intvl.low + (1 - j) * r->bbox.y_intvl.low;
                  auto z = k * r->bbox.z_intvl.low + (1 - k) * r->bbox.z_intvl.low;

                  auto newx = r->cos_theta * x + r->sin_theta * z;
                  auto newz = -r->sin_theta * x + r->cos_theta * z;

                  auto tester = (vec3_t){ .x = newx, .y = y, .z = newz };

                  for (int c = 0; c < 3; c++)
                    {
                      min.element[c] = fmin (min.element[c], tester.element[c]);
                      max.element[c] = fmax (max.element[c], tester.element[c]);
                    }
                }
            }
        }

      r->bbox     = aabb_from_points (&min, &max);
      r->hit_type = ROTATE;
      r->hit      = rotate_y_hit;
      r->object   = object;
    }
  return r;
}
