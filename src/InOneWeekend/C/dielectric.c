#include "dielectric.h"
#include "color.h"
#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include <stdlib.h>

bool
dielectric_scatter (ray const r_in, hit_record const *rec, color *attenuation, ray *scattered)
{
  dielectric *diel = (dielectric *)rec->mat;
  *attenuation     = (color){ .r = 1.0, .g = 1.0, .b = 1.0 };
  double ri        = rec->front_face ? (1.0 / diel->refraction_index) : diel->refraction_index;

  vec3 unit_direction = vec3_unit (r_in.direction);
  vec3 refracted      = refract (unit_direction, rec->normal, ri);

  *scattered = (ray){ rec->p, refracted };
  return true;
}

dielectric *
dielectric_new (double refraction_index)
{
  dielectric *diel = malloc (sizeof (*diel));
  if (diel)
    {
      ((material *)diel)->scatter = dielectric_scatter;
      diel->refraction_index      = refraction_index;
    }
  return diel;
}
