#pragma once

#include "color.h"
#include "material.h"

typedef struct metal
{
  material *mat;
  color     albedo;
} metal;

metal *metal_new (color albedo);
