#include "metal.h"
#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include <stdlib.h>

bool
metal_scatter (ray const r_in, hit_record const *rec, color *attenuation, ray *scattered)
{
  metal *m         = (metal *)rec->mat;
  vec3   reflected = vec3_reflect (r_in.direction, rec->normal);
  reflected        = vec3_add (vec3_unit (reflected), vec3_scalar_mult (vec3_random_unit_vector (), m->fuzz));
  *attenuation     = m->albedo;
  *scattered       = (ray){ rec->p, reflected };
  return true;
}

metal *
metal_new (color albedo, double fuzz)
{
  metal *met = malloc (sizeof (*met));
  if (met)
    {
      ((material *)met)->scatter = metal_scatter;
      met->albedo                = albedo;
      met->fuzz                  = fuzz < 1 ? fuzz : 1;
    }
  return met;
}
