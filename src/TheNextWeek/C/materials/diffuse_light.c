#include "diffuse_light.h"
#include "color.h"
#include "solid_color.h"
#include "texture.h"
#include <stdbool.h>
#include <stdlib.h>

// Our diffuse_light material always refracts if physically possible.
static bool
diffuse_light_scatter (ray_t const ray, hit_record_t const *rec, color_t *attenuation, ray_t *scattered)
{
  (void)ray;
  (void)rec;
  (void)attenuation;
  (void)scattered;

  return false;
}

static color_t
diffuse_light_emit (hit_record_t const *rec)
{
  auto dl = (diffuse_light_t *)get_material (rec->object);
  return dl->tex->value (dl->tex, rec->u, rec->v, &rec->p);
}

// Returns `NULL` if memory allocation failed.
diffuse_light_t *
diffuse_light_from_texture (texture_t *tex)
{
  diffuse_light_t *d = malloc (sizeof (*d));
  if (d)
    {
      d->scatter = diffuse_light_scatter;
      d->emit    = diffuse_light_emit;
      d->tex     = tex;
    }
  return d;
}

// Returns `NULL` if memory allocation failed.
diffuse_light_t *
diffuse_light_from_color (color_t color)
{
  solid_color_t *sc = solid_color_from_color (color);
  return diffuse_light_from_texture ((texture_t *)sc);
}
