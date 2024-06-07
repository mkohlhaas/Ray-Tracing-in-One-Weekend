#include "dielectric.h"
#include "color.h"
#include "hit_record.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>
#include <stdlib.h>

// Schlick's approximation for reflectance.
static double
dielectric_reflectance (double cosine, double refraction_index)
{
  auto r0 = (1 - refraction_index) / (1 + refraction_index);
  r0      = r0 * r0;
  return r0 + (1 - r0) * pow ((1 - cosine), 5);
}

bool
dielectric_scatter (ray const r_in, hit_record const *rec, color *attenuation, ray *scattered)
{
  dielectric *diel = (dielectric *)rec->mat;
  *attenuation     = white; // no attenuation
  double ri        = rec->front_face ? (1.0 / diel->refraction_index) : diel->refraction_index;

  vec3   unit_direction = vec3_unit (r_in.direction);
  double cos_theta      = fmin (vec3_dot_product (vec3_minus (unit_direction), rec->normal), 1.0);
  double sin_theta      = sqrt (1.0 - cos_theta * cos_theta);
  bool   cannot_refract = ri * sin_theta > 1.0;

  vec3 direction;
  if (cannot_refract || dielectric_reflectance (cos_theta, ri) > random_double ())
    {
      direction = vec3_reflect (unit_direction, rec->normal);
    }
  else
    {
      direction = refract (unit_direction, rec->normal, ri);
    }

  *scattered = (ray){ rec->p, direction };

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
