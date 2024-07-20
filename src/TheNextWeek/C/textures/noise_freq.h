#pragma once

#include "noise/perlin_freq.h"
#include "textures/texture.h"

typedef struct noise_freq_texture
{
  value_fn       value;
  perlin_freq_t *noise;
  double         scale;
} noise_freq_texture_t;

noise_freq_texture_t *noise_freq_texture_new (double scale);
