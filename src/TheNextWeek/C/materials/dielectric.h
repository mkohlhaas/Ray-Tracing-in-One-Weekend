#pragma once

#include "color.h"
#include "material.h"
#include "texture.h"

typedef struct dielectric
{
  scatter_fn scatter;
  emit_fn    emit;
  double     refraction_index;
  texture_t *tex;
} dielectric_t;

dielectric_t *dielectric_new_with_tex (double refraction_index, texture_t *tex);
dielectric_t *dielectric_from_color (double refraction_index, color_t albedo);
