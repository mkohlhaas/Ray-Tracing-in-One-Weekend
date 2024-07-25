#pragma once

#include "color.h"
#include "material.h"
#include "texture.h"

typedef struct diffuse_light
{
  scatter_fn scatter;
  emit_fn    emit;
  texture_t *tex;
} diffuse_light_t;

diffuse_light_t *diffuse_light_from_texture (texture_t *tex);
diffuse_light_t *diffuse_light_from_color (color_t color);
