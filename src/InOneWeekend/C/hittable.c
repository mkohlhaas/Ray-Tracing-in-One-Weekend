#include "hittable.h"
#include "hit_record.h"
#include "ray.h"
#include <stdlib.h>

hittable *
hittable_new (hit_fn hit, void *object)
{
  hittable *h = malloc (sizeof (*h));
  if (h)
    {
      h->hit    = hit;
      h->object = object;
    }
  return h;
}

// The parameter `outward_normal` is assumed to have unit length.
void
set_face_normal (hit_record *rec, struct ray const r, vec3 const outward_normal)
{

  rec->front_face = vec3_dot_product (r.direction, outward_normal) < 0;
  rec->normal     = rec->front_face ? outward_normal : vec3_minus (outward_normal);
}
