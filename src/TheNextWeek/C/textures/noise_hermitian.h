#pragma once

#include "perlin_hermitian.h"
#include "texture.h"

typedef struct noise_hermitian_texture
{
  value_fn            value;
  perlin_hermitian_t *noise;
} noise_hermitian_texture_t;

noise_hermitian_texture_t *noise_hermitian_texture_new ();
