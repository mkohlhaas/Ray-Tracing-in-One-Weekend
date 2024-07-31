#pragma once

#include "color.h"
#include "material.h"
#include "texture.h"

typedef struct isotropic
{
  scatter_fn scatter;
  emit_fn    emit;
  texture_t *tex;
} isotropic_t;

isotropic_t *isotropic_from_color (color_t albedo);
isotropic_t *isotropic_from_tex (texture_t *tex);
