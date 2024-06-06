#pragma once

#include "material.h"

typedef struct dielectric
{
  material *mat;
  double    refraction_index;
} dielectric;

dielectric *dielectric_new (double refraction_index);
