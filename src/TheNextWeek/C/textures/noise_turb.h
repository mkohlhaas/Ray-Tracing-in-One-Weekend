#pragma once

#include "noise/perlin_turb.h"
#include "textures/texture.h"

typedef struct noise_turb_texture
{
  value_fn       value;
  perlin_turb_t *noise;
  double         scale;
} noise_turb_texture_t;

noise_turb_texture_t *noise_turb_texture_new (double scale);
