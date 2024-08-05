#include "materials/dielectric.h"
#include "color.h"
#include "solid_color.h"
#include "texture.h"
#include "utils/utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Reflectivity varies with angle.
// Schlick's approximation for reflectance.
static double
dielectric_reflectance (double cosine, double refraction_index)
{
  auto r0 = (1 - refraction_index) / (1 + refraction_index);
  r0      = r0 * r0;
  return r0 + (1 - r0) * pow ((1 - cosine), 5);
}

// Our dielectric material always refracts if physically possible.
static bool
dielectric_scatter (ray_t const ray, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  // scattered ray
  auto diel           = (dielectric_t *)get_material (rec->object);
  auto refraction_idx = rec->front_face ? (1.0 / diel->refraction_index) : diel->refraction_index;
  auto unit_direction = vec3_unit (ray.direction);
  auto cos_theta      = fmin (vec3_dot (vec3_uminus (unit_direction), rec->unit_normal), 1.0);
  auto sin_theta      = sqrt (1.0 - cos_theta * cos_theta);
  auto cannot_refract = refraction_idx * sin_theta > 1.0;

  vec3_t direction;
  if (cannot_refract || dielectric_reflectance (cos_theta, refraction_idx) > random_double ())
    {
      direction = vec3_reflect (unit_direction, rec->unit_normal);
    }
  else
    {
      direction = vec3_refract (unit_direction, rec->unit_normal, refraction_idx);
    }

  // return values
  // *attenuation = white; // no attenuation
  *attenuation = diel->tex->value (diel->tex, rec->u, rec->v, &rec->p);
  *scattered   = (ray_t){ rec->p, direction, ray.tm };

  return true; // material, not light source
}

static color_t
dielectric_emit (hit_record_t const *rec)
{
  (void)rec;

  return black;
}

// Returns `NULL` if memory allocation failed.
dielectric_t *
dielectric_new_with_tex (double refraction_index, texture_t *tex)
{
  dielectric_t *d = malloc (sizeof (*d));
  if (d)
    {
      d->scatter          = dielectric_scatter;
      d->emit             = dielectric_emit;
      d->refraction_index = refraction_index;
      d->tex              = tex;
    }
  return d;
}

dielectric_t *
dielectric_from_color (double refraction_index, color_t albedo)
{
  return dielectric_new_with_tex (refraction_index, (texture_t *)solid_color_from_color (albedo));
}
