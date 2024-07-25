#pragma once

#include "materials/material.h"
#include "math/color.h"
#include "textures/texture.h"

// `lambertian` is a `material`.
typedef struct lambertian
{
  scatter_fn scatter;
  emit_fn    emit;
  texture_t *tex;
} lambertian_t;

lambertian_t *lambertian_new (color_t albedo);
lambertian_t *lambertian_new_with_tex (texture_t *tex);
