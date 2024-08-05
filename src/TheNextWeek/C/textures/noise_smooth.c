#include "noise_smooth.h"
#include "color.h"
#include "error.h"
#include "perlin_smooth.h"
#include "texture.h"
#include "vec3.h"

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;

  noise_smooth_texture_t *nt = (noise_smooth_texture_t *)tex;
  return vec3_mult (perlin_smooth_noise (nt->noise, point), grey);
}

noise_smooth_texture_t *
noise_smooth_texture_new ()
{
  noise_smooth_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value = value;
  nt->noise = perlin_smooth_new ();
  return nt;
}
