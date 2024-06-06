#pragma once

#include "color.h"
#include "material.h"

typedef struct lambertian
{
  material *mat;
  color     albedo;
} lambertian;

lambertian *lambertian_new (color albedo);
