#include "noise_phase.h"
#include "color.h"
#include "error.h"
#include "perlin_phase.h"
#include "point.h"
#include "texture.h"
#include "vec3.h"
#include <math.h>

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;
  noise_phase_texture_t *nt = (noise_phase_texture_t *)tex;

  int depth = 10;
  return vec3_mult (1 + sin (nt->scale * point->z + 10 * perlin_phase_noise (nt->noise, point, depth)), light_grey);
}

noise_phase_texture_t *
noise_phase_texture_new (double scale)
{
  noise_phase_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value = value;
  nt->noise = perlin_phase_new ();
  nt->scale = scale;
  return nt;
}
