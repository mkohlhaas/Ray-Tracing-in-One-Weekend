#pragma once

#include "material.h"
#include <stdbool.h>

typedef struct hit_record
{
  void     *object;
  point3    p;
  vec3      normal; // normals always point against the ray
  material *mat;
  double    t;
  bool      front_face;
} hit_record;
