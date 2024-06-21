#pragma once

#include "material.h"

typedef struct dielectric
{
  scatter_fn scatter;
  double     refraction_index;
} dielectric;

dielectric *dielectric_new (double refraction_index);
