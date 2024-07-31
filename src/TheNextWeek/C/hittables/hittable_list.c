#include "hittables/hittable_list.h"
#include "3rd_party/stb_ds.h"
#include "bbox/aabb.h"
#include "math/interval.h"
#include "ray/ray.h"

// Returns `true` if something got hit.
// Returns `hit_record` in `rec` if something got hit.
static bool
hittable_list_hit (ray_t const ray, hittable_t *object, interval_t intvl, hit_record_t *rec)
{
  hittable_list_t *l = (hittable_list_t *)object;
  hit_record_t     obj_hit;
  auto             closest_so_far = intvl.high;
  bool             hit_anything   = false;
  for (uint i = 0; i < arrlen (l->hittables); i++)
    {
      if (l->hittables[i]->hit (ray, l->hittables[i], (interval_t){ intvl.low, closest_so_far }, &obj_hit))
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
  hittable_list_t *h = malloc (sizeof *h);
  if (h)
    {
      h->hit_type  = HITTABLE_LIST;
      h->hit       = hittable_list_hit;
      h->bbox      = aabb_new_empty ();
      h->hittables = NULL;
    }
  return h;
}

void
hittable_list_add (hittable_list_t *l, hittable_t *h)
{
  l->bbox = aabb_from_aabbs (&l->bbox, &h->bbox);
  arrput (l->hittables, h);
}

void
hittable_list_print (hittable_list_t *l, int indent_lvl)
{

  fprintf (stderr, "%*sHittable list: (%f %f) (%f %f) (%f %f)\n", indent_lvl, "", l->bbox.x_intvl.low,
           l->bbox.x_intvl.high, l->bbox.z_intvl.low, l->bbox.z_intvl.high, l->bbox.z_intvl.low, l->bbox.z_intvl.high);
}
