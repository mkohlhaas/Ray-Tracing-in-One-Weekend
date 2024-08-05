#include "noise_hermitian.h"
#include "color.h"
#include "error.h"
#include "perlin_hermitian.h"
#include "texture.h"
#include "vec3.h"

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;

  noise_hermitian_texture_t *nt = (noise_hermitian_texture_t *)tex;
  return vec3_mult (perlin_hermitian_noise (nt->noise, point), grey);
}

noise_hermitian_texture_t *
noise_hermitian_texture_new ()
{
  noise_hermitian_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value = value;
  nt->noise = perlin_hermitian_new ();
  return nt;
}
