#include "noise_freq.h"
#include "color.h"
#include "error.h"
#include "perlin_freq.h"
#include "point.h"
#include "texture.h"
#include "vec3.h"

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;
  noise_freq_texture_t *nt = (noise_freq_texture_t *)tex;

  auto point_scaled = vec3_mult (nt->scale, *point);
  return vec3_mult (perlin_freq_noise (nt->noise, &point_scaled), (color_t){ .r = 1, .g = 1, .b = 1 });
}

noise_freq_texture_t *
noise_freq_texture_new (double scale)
{
  noise_freq_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value = value;
  nt->noise = perlin_freq_new ();
  nt->scale = scale;
  return nt;
}
