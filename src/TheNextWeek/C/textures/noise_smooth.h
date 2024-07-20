#pragma once

#include "noise/perlin_smooth.h"
#include "textures/texture.h"

typedef struct noise_smooth_texture
{
  value_fn         value;
  perlin_smooth_t *noise;
} noise_smooth_texture_t;

noise_smooth_texture_t *noise_smooth_texture_new ();
