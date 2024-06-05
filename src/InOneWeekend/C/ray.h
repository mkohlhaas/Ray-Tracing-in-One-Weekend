#pragma once

#include "camera.h"
#include "color.h"

typedef struct ray
{
  point3 origin;
  vec3   direction;
} ray;

point3 point_at (ray r, double t);
color  ray_color (ray const r, int depth, struct hittable **world);
ray    get_ray (camera c, int row, int col);
