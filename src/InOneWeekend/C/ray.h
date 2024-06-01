#pragma once

#include "vec3.h"

typedef struct
{
  point3 orig;
  vec3   dir;
} ray;

point3 ray_at (ray r, double t);
