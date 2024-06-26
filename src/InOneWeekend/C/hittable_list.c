#include "hittable_list.h"
#include "ray.h"

// Returns `true` if something got hit.
// Returns `hit_record` in `rec` if something got hit.
static bool
hittable_list_hit (ray_t const ray, interval_t itvl, hit_record_t *rec)
{
  hittable_list_t *l = (hittable_list_t *)rec->object;
  hit_record_t     obj_hit;
  auto             closest_so_far = itvl.max;
  bool             hit_anything   = false;
  for (uint i = 0; i < arrlen (l->hittables); i++)
    {
      obj_hit.object = (hittable_t *)l->hittables[i];
      if (obj_hit.object->hit_fn (ray, (interval_t){ 0.001, closest_so_far }, &obj_hit))
        {
          hit_anything = true;
          if (obj_hit.t < closest_so_far)
            {
              *rec           = obj_hit;
              closest_so_far = rec->t;
            }
        };
    }

  return hit_anything;
}

// Returns NULL if memory allocation failed.
hittable_list_t *
hittable_list_new ()
{
  hittable_list_t *h = malloc (sizeof (*h));
  if (h)
    {
      h->type      = LIST;
      h->hit_fn    = hittable_list_hit;
      h->hittables = NULL;
    }
  return h;
}
