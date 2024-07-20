#include "textures/noise_lattice.h"
#include "error/error.h"
#include "math/color.h"
#include "math/vec3.h"
#include "noise/perlin_lattice.h"
#include "point.h"
#include "textures/texture.h"

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;
  noise_lattice_texture_t *nt = (noise_lattice_texture_t *)tex;

  auto point_scaled = vec3_mult (nt->scale, *point);
  return vec3_mult (0.5 * (1.0 + perlin_lattice_noise (nt->noise, &point_scaled)), grey);
}

noise_lattice_texture_t *
noise_lattice_texture_new (double scale)
{
  noise_lattice_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value = value;
  nt->noise = perlin_lattice_new ();
  nt->scale = scale;
  return nt;
}
