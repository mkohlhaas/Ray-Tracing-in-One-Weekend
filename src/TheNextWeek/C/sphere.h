#pragma once

#include "material.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct sphere
{
  hit_type_t  type; // SPHERE
  hit_fn      hit_fn;
  point3      center_start;
  vec3_t      center_vec;
  double      radius;
  material_t *mat;
} sphere_t;

struct hit_record;
struct ray;
sphere_t *sphere_new (point3 center_start, point3 center_end, double radius, material_t *mat);
