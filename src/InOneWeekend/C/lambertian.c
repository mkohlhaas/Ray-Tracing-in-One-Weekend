#include "lambertian.h"
#include "hit_record.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include <stdlib.h>

static bool
lambertian_scatter (ray const r_in, hit_record const *rec, color *attenuation, ray *scattered)
{
  (void)r_in;

  lambertian *lam = (lambertian *)rec->mat;

  vec3 scatter_dir = vec3_add (rec->normal, vec3_random_unit_vector ());

  // Catch degenerate scatter direction.
  if (vec3_near_zero (scatter_dir))
    {
      scatter_dir = rec->normal;
    }

  *attenuation = lam->albedo;
  *scattered   = (ray){ rec->p, scatter_dir };
  return true;
}

lambertian *
lambertian_new (color albedo)
{
  lambertian *lam = malloc (sizeof (*lam));
  if (lam)
    {
      ((material *)lam)->scatter = lambertian_scatter;
      lam->albedo                = albedo;
    }
  return lam;
}
