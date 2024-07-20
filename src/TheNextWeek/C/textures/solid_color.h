#pragma once

#include "math/color.h"
#include "textures/texture.h"

// `solid_color` is a `texture`.
typedef struct solid_color
{
  value_fn value;
  color_t  albedo;
} solid_color_t;

solid_color_t *solid_color_from_color (color_t albedo);
solid_color_t *solid_color_from_rgb (double red, double green, double blue);
