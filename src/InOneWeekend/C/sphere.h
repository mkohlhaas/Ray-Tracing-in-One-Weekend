#pragma once

#include "material.h"
#include <stdbool.h>

typedef struct
{
  hit_type_t  type;
  hit_fn      hit_fn;
  point3      center;
  double      radius;
  material_t *mat;
} sphere;

struct hit_record;
struct ray;
sphere *sphere_new (point3 center, double radius, material_t *mat);
