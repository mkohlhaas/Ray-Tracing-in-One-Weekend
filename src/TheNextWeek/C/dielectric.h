#pragma once

#include "material.h"

typedef struct dielectric
{
  scatter_fn scatter;
  double     refraction_index;
} dielectric_t;

dielectric_t *dielectric_new (double refraction_index);
