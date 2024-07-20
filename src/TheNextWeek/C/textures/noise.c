#include "textures/noise.h"
#include "error/error.h"
#include "math/color.h"
#include "math/vec3.h"
#include "noise/perlin.h"
#include "textures/texture.h"

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;

  noise_texture_t *nt = (noise_texture_t *)tex;
  return vec3_mult (perlin_noise (nt->noise, point, nt->granularity), grey);
}

noise_texture_t *
noise_texture_new (int granularity)
{
  noise_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value       = value;
  nt->noise       = perlin_new ();
  nt->granularity = granularity;
  return nt;
}
