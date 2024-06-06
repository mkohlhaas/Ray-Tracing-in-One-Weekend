#include "metal.h"
#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include <stdlib.h>

bool
metal_scatter (void *self, ray const r_in, hit_record const *rec, color *attenuation, ray *scattered)
{
  metal *m         = (metal *)self;
  vec3   reflected = vec3_reflect (r_in.direction, rec->normal);
  *attenuation     = m->albedo;
  *scattered       = *ray_new (rec->p, reflected);
  return true;
}

metal *
metal_new (color albedo)
{
  metal    *m   = malloc (sizeof (*m));
  material *mat = malloc (sizeof (material));
  if (m && mat)
    {
      m->mat          = mat;
      m->mat->scatter = metal_scatter;
      m->mat->self    = m;
      m->albedo       = albedo;
    }
  return m;
}
