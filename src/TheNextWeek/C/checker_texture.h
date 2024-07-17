#pragma once

#include "texture.h"

// `checker_texture` is a `texture`.
typedef struct checker_texture
{
  value_fn   value;
  double     inv_scale;
  texture_t *even;
  texture_t *odd;
} checker_texture_t;

checker_texture_t *checker_texture_from_textures (double scale, texture_t *even, texture_t *odd);
checker_texture_t *checker_texture_from_colors (double scale, color_t const *c1, color_t const *c2);
