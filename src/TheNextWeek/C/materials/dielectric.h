#pragma once

#include "materials/material.h"

typedef struct dielectric
{
  scatter_fn scatter;
  emit_fn    emit;
  double     refraction_index;
} dielectric_t;

dielectric_t *dielectric_new (double refraction_index);
