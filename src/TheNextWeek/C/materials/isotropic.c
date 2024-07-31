#include "isotropic.h"
#include "solid_color.h"
#include "vec3.h"
#include <stdlib.h>

static bool
isotropic_scatter (ray_t const ray, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  auto iso     = (isotropic_t *)get_material (rec->object);
  *scattered   = (ray_t){ rec->p, vec3_random_unit_vector_in_sphere (), ray.tm };
  *attenuation = iso->tex->value (iso->tex, rec->u, rec->v, &rec->p);
  return true;
}

static color_t
isotropic_emit (hit_record_t const *rec)
{
  (void)rec;

  return black;
}

// Returns `NULL` if memory allocation failed.
isotropic_t *
isotropic_from_color (color_t albedo)
{
  isotropic_t *iso = malloc (sizeof *iso);
  if (iso)
    {
      iso->scatter = isotropic_scatter;
      iso->emit    = isotropic_emit;
      iso->tex     = (texture_t *)solid_color_from_color (albedo);
    }
  return iso;
}

// Returns `NULL` if memory allocation failed.
isotropic_t *
isotropic_from_tex (texture_t *tex)
{
  isotropic_t *iso = malloc (sizeof *iso);
  if (iso)
    {
      iso->scatter = isotropic_scatter;
      iso->emit    = isotropic_emit;
      iso->tex     = tex;
    }
  return iso;
}
