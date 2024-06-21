#include "lambertian.h"
#include <stdlib.h>

static void
lambertian_scatter (ray_t const r_in, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  (void)r_in;

  lambertian_t *lam         = (lambertian_t *)get_material (rec->object);
  vec3_t        scatter_dir = vec3_add (rec->normal, vec3_random_unit_vector ());

  // Catch degenerate scatter direction.
  if (vec3_near_zero (scatter_dir))
    {
      scatter_dir = rec->normal;
    }

  *attenuation = lam->albedo;
  *scattered   = (ray_t){ rec->p, scatter_dir };
}

lambertian_t *
lambertian_new (color_t albedo)
{
  lambertian_t *lam = malloc (sizeof (*lam));
  // TODO: exit/abort if failure
  if (lam)
    {
      lam->scatter = lambertian_scatter;
      lam->albedo  = albedo;
    }
  return lam;
}
