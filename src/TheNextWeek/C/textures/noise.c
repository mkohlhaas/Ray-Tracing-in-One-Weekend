#include "noise.h"
#include "color.h"
#include "error.h"
#include "perlin.h"
#include "texture.h"
#include "vec3.h"

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
