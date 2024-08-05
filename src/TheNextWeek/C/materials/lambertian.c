#include "lambertian.h"
#include "solid_color.h"
#include "texture.h"
#include <stdbool.h>
#include <stdlib.h>

// Returns `attenuation` and `scattered` ray.
static bool
lambertian_scatter (ray_t const ray, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  auto l           = (lambertian_t *)get_material (rec->object);
  auto scatter_dir = vec3_add (rec->unit_normal, vec3_random_unit_vector_in_sphere ());

  // Catch degenerate scatter direction.
  if (vec3_near_zero (scatter_dir))
    {
      scatter_dir = rec->unit_normal;
    }

  // *attenuation = l->albedo;
  *attenuation = l->tex->value (l->tex, rec->u, rec->v, &rec->p);
  *scattered   = (ray_t){ rec->p, scatter_dir, ray.tm };

  return true; // material, not light source
}

static color_t
lambertian_emit (hit_record_t const *rec)
{
  (void)rec;

  return black;
}

// Returns `NULL` if memory allocation failed.
lambertian_t *
lambertian_new (color_t albedo)
{
  return lambertian_new_with_tex ((texture_t *)solid_color_from_color (albedo));
}

// Returns `NULL` if memory allocation failed.
lambertian_t *
lambertian_new_with_tex (texture_t *tex)
{
  lambertian_t *lam = malloc (sizeof (*lam));
  if (lam)
    {
      lam->scatter = lambertian_scatter;
      lam->emit    = lambertian_emit;
      lam->tex     = tex;
    }
  return lam;
}
