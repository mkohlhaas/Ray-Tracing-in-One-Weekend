#pragma once

#include "noise/perlin_phase.h"
#include "textures/texture.h"

typedef struct noise_phase_texture
{
  value_fn        value;
  perlin_phase_t *noise;
  double          scale;
} noise_phase_texture_t;

noise_phase_texture_t *noise_phase_texture_new (double scale);
