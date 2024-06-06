#include "lambertian.h"
#include "hit_record.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include <stdlib.h>

static bool
lambertian_scatter (void *self, ray const r_in, hit_record const *rec, color *attenuation, ray *scattered)
{
  (void)r_in;

  lambertian *l = (lambertian *)self;

  vec3 scatter_dir = vec3_add (rec->normal, vec3_random_unit_vector ());

  // Catch degenerate scatter direction
  if (vec3_near_zero (scatter_dir))
    {
      scatter_dir = rec->normal;
    }

  *attenuation = l->albedo;
  *scattered   = *ray_new (rec->p, scatter_dir);
  return true;
}

lambertian *
lambertian_new (color albedo)
{
  lambertian *l   = malloc (sizeof (*l));
  material   *mat = malloc (sizeof (material));
  if (l && mat)
    {
      l->mat          = mat;
      l->mat->scatter = lambertian_scatter;
      l->mat->self    = l;
      l->albedo       = albedo;
    }
  return l;
}
