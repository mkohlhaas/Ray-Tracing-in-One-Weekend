#pragma once

#include "material.h"

typedef struct metal
{
  scatter_fn scatter;
  color_t    albedo;
  double     fuzz;
} metal;

metal *metal_new (color_t albedo, double fuzz);
