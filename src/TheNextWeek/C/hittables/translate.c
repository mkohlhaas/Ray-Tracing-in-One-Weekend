#include "translate.h"
#include "aabb.h"
#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"
#include <stdlib.h>

static bool
translate_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  translate_t *t = (translate_t *)object;

  // Move the ray backwards by the offset
  auto offset_origin = vec3_sub (ray.origin, t->offset);
  auto offset_ray    = (ray_t){ offset_origin, ray.direction, ray.tm };

  // Determine whether an intersection exists along the offset ray (and if so, where)
  if (!t->object->hit (offset_ray, t->object, intvl, rec))
    {
      return false;
    }
  else
    {
      // Move the intersection point forwards by the offset
      rec->p = vec3_add (rec->p, t->offset);
      return true;
    }
}

translate_t *
translate_new (hittable_t *object, vec3_t offset)
{
  translate_t *t = malloc (sizeof (*t));
  if (t)
    {
      t->hit_type = TRANSLATE;
      t->hit      = translate_hit;
      t->bbox     = aabb_add_offset (object->bbox, offset);
      t->object   = object;
      t->offset   = offset;
    }
  return t;
}
