#pragma once

#include "noise/perlin_hermitian.h"
#include "textures/texture.h"

typedef struct noise_hermitian_texture
{
  value_fn            value;
  perlin_hermitian_t *noise;
} noise_hermitian_texture_t;

noise_hermitian_texture_t *noise_hermitian_texture_new ();
