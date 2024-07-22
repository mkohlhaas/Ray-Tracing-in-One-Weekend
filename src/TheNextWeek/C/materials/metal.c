#include "materials/metal.h"
#include <stdbool.h>
#include <stdlib.h>

// Returns `attenuation` and `scattered` ray.
static bool
metal_scatter (ray_t const ray, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  // calculate reflected ray using metal's fuzziness
  auto m         = (metal *)get_material (rec->object);
  auto fuzzy     = vec3_mult (m->fuzz, vec3_random_unit_vector_in_sphere ());
  auto reflected = vec3_reflect (ray.direction, rec->unit_normal);
  reflected      = vec3_unit (reflected);
  reflected      = vec3_add (reflected, fuzzy);

  // setting return values
  *attenuation = m->albedo;
  *scattered   = (ray_t){ rec->p, reflected, ray.tm };

  return true; // material, not light source
}

// Returns `NULL` if memory allocation failed.
metal *
metal_new (color_t albedo, double fuzz)
{
  metal *met = malloc (sizeof *met);
  if (met)
    {
      met->scatter = metal_scatter;
      met->albedo  = albedo;
      met->fuzz    = fuzz < 1 ? fuzz : 1;
    }
  return met;
}
