#include "dielectric.h"
#include "utils.h"
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

void
dielectric_scatter (ray_t const ray, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  // attenuation
  *attenuation = white; // no attenuation

  // scattered ray
  auto diel           = (dielectric_t *)get_material (rec->object);
  auto refraction_idx = rec->front_face ? (1.0 / diel->refraction_index) : diel->refraction_index;
  auto unit_direction = vec3_unit (ray.direction);
  auto cos_theta      = fmin (vec3_dot (vec3_minus (unit_direction), rec->normal), 1.0);
  auto sin_theta      = sqrt (1.0 - cos_theta * cos_theta);
  auto cannot_refract = refraction_idx * sin_theta > 1.0;

  vec3_t direction;
  if (cannot_refract || dielectric_reflectance (cos_theta, refraction_idx) > random_double ())
    {
      direction = vec3_reflect (unit_direction, rec->normal);
    }
  else
    {
      direction = vec3_refract (unit_direction, rec->normal, refraction_idx);
    }

  *scattered = (ray_t){ rec->p, direction };
}

dielectric_t *
dielectric_new (double refraction_index)
{
  dielectric_t *d = malloc (sizeof (*d));
  // TODO: exit/abort if failure | calling fn checks return value
  if (d)
    {
      d->scatter          = dielectric_scatter;
      d->refraction_index = refraction_index;
    }
  return d;
}
