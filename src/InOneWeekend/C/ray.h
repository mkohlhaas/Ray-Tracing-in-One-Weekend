#pragma once

#include "camera.h"
#include "color.h"

typedef struct ray
{
  point3 origin;
  vec3   direction;
} ray;

ray   *ray_new (point3 origin, vec3 direction);
point3 point_at (ray r, double t);
color  ray_color (ray const r, int depth, struct hittable *world[]);
ray    get_ray (camera c, int row, int col);
vec3   refract (const vec3 uv, const vec3 n, double etai_over_etat);
