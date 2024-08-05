#include "solid_color.h"
#include "error.h"
#include <stdlib.h>

static color_t
value (texture_t *tex, double u, double v, point3_t const *p)
{
  (void)u;
  (void)v;
  (void)p;

  solid_color_t *sc = (solid_color_t *)tex;
  return sc->albedo;
}

solid_color_t *
solid_color_from_color (color_t albedo)
{
  solid_color_t *sc = malloc (sizeof *sc);
  if (!sc)
    {
      logExit ("Out of memory");
    }

  sc->value  = value;
  sc->albedo = albedo;

  return sc;
}

solid_color_t *
solid_color_from_rgb (double red, double green, double blue)
{
  solid_color_t *sc = malloc (sizeof *sc);
  if (!sc)
    {
      logExit ("Out of memory");
    }

  sc->value    = value;
  sc->albedo.r = red;
  sc->albedo.g = green;
  sc->albedo.b = blue;

  return sc;
}
