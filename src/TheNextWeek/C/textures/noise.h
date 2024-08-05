#pragma once

#include "perlin.h"
#include "texture.h"

typedef struct noise_texture
{
  value_fn  value;
  perlin_t *noise;
  int       granularity;
} noise_texture_t;

noise_texture_t *noise_texture_new (int granularity);
