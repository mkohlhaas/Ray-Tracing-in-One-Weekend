#pragma once

#include "color.h"
#include "point.h"
#include "vec3.h"

typedef struct
{
  point3 orig;
  vec3   direction;
} ray;

point3 ray_at (ray r, double t);
color  ray_color (ray const r);
