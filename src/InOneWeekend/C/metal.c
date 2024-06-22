#include "metal.h"
#include <stdlib.h>

// Returns `attenuation` and `scattered` ray.
void
metal_scatter (ray_t const r_in, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  metal *m         = (metal *)get_material (rec->object);
  vec3_t reflected = vec3_reflect (r_in.direction, rec->normal);
  reflected        = vec3_add (vec3_unit (reflected), vec3_scalar_mult (vec3_random_unit_vector (), m->fuzz));

  *attenuation = m->albedo;
  *scattered   = (ray_t){ rec->p, reflected };
}

metal *
metal_new (color_t albedo, double fuzz)
{
  metal *met = malloc (sizeof (*met));
  // TODO: exit/abort if failure | calling fn checks return value
  if (met)
    {
      met->scatter = metal_scatter;
      met->albedo  = albedo;
      met->fuzz    = fuzz < 1 ? fuzz : 1;
    }
  return met;
}
