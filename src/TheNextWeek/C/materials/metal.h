#pragma once

#include "material.h"

typedef struct metal
{
  scatter_fn scatter;
  emit_fn    emit;
  color_t    albedo;
  double     fuzz;
} metal_t;

metal_t *metal_new (color_t albedo, double fuzz);
