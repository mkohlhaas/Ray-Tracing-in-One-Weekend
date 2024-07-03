#pragma once

#include "color.h"
#include "material.h"

typedef struct lambertian
{
  scatter_fn scatter;
  color_t    albedo;
} lambertian_t;

lambertian_t *lambertian_new (color_t albedo);
