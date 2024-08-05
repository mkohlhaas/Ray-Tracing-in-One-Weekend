#include "noise_turb.h"
#include "color.h"
#include "error.h"
#include "perlin_turb.h"
#include "point.h"
#include "texture.h"
#include "vec3.h"

static color_t
value (texture_t *tex, double u, double v, point3_t const *point)
{
  (void)u;
  (void)v;
  noise_turb_texture_t *nt = (noise_turb_texture_t *)tex;

  int depth = 10;
  return vec3_mult (perlin_turb_turbulence (nt->noise, point, depth), grey);
}

noise_turb_texture_t *
noise_turb_texture_new (double scale)
{
  noise_turb_texture_t *nt = malloc (sizeof *nt);
  if (!nt)
    {
      logExit ("Out of memory");
    }
  nt->value = value;
  nt->noise = perlin_turb_new ();
  nt->scale = scale;
  return nt;
}
