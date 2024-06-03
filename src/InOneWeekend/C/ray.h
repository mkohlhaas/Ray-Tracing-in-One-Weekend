#pragma once

#include "color.h"
#include "point.h"
#include "vec3.h"
#include <glib.h>

typedef struct
{
  point3 origin;
  vec3   direction;
} ray;

point3 point_at (ray r, double t);
color  ray_color (ray const r, GArray *const world);
