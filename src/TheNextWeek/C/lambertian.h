#pragma once

#include "color.h"
#include "material.h"
#include "texture.h"

// `lambertian` is a `material`.
typedef struct lambertian
{
  scatter_fn scatter;
  texture_t *tex;
} lambertian_t;

lambertian_t *lambertian_new (color_t albedo);
lambertian_t *lambertian_new_with_tex (texture_t *tex);
