#include "textures/checker.h"
#include "error/error.h"
#include "textures/solid_color.h"
#include <math.h>
#include <stdlib.h>

static color_t
value (texture_t *tex, double u, double v, point3_t const *p)
{
  checker_texture_t *ct = (checker_texture_t *)tex;

  auto x = (int)(floor (ct->inv_scale * p->x));
  auto y = (int)(floor (ct->inv_scale * p->y));
  auto z = (int)(floor (ct->inv_scale * p->z));

  bool isEven = (x + y + z) % 2 == 0;

  return isEven ? ct->even->value (ct->even, u, v, p) : ct->odd->value (ct->odd, u, v, p);
}

checker_texture_t *
checker_texture_from_textures (double scale, texture_t *even, texture_t *odd)
{
  checker_texture_t *ct = malloc (sizeof *ct);
  if (!ct)
    {
      logExit ("Out of memory");
    }

  ct->value     = value;
  ct->inv_scale = 1.0 / scale;
  ct->even      = even;
  ct->odd       = odd;

  return ct;
}

checker_texture_t *
checker_texture_from_colors (double scale, color_t const *c1, color_t const *c2)
{
  checker_texture_t *ct = malloc (sizeof *ct);
  if (!ct)
    {
      logExit ("Out of memory");
    }

  ct->value     = value;
  ct->inv_scale = 1.0 / scale;
  ct->even      = (texture_t *)solid_color_from_color (*c1);
  ct->odd       = (texture_t *)solid_color_from_color (*c2);

  return ct;
}
