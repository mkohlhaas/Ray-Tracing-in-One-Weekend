#pragma once

#include "perlin_lattice.h"
#include "texture.h"

typedef struct noise_lattice_texture
{
  value_fn          value;
  perlin_lattice_t *noise;
  double            scale;
} noise_lattice_texture_t;

noise_lattice_texture_t *noise_lattice_texture_new (double scale);
