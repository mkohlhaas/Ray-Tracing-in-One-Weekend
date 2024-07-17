#pragma once

#include "color.h"
#include "point.h"

struct texture;
typedef color_t (*value_fn) (struct texture *tex, double u, double v, point3_t const *p);

typedef struct texture
{
  value_fn value;
} texture_t;
