#pragma once

#include "color.h"
#include "material.h"

typedef struct metal
{
  material *mat;
  color     albedo;
  double    fuzz;
} metal;

metal *metal_new (color albedo, double fuzz);
